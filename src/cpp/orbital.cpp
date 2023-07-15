#include "orbital.hpp"

#include <cassert>
#include <random>
#include <thread>

#include "../math/bohr.hpp"
#include "../math/coordinates.hpp"
#include "../math/trigonometry.hpp"
#include "../math/wave_function.hpp"
#include "../util/performance.hpp"
#include "engine/shapes.hpp"

namespace orbitals {

Orbital::Orbital() : m_Position(0, 0, 0), m_N{1}, m_L{0}, m_M{0} {
  initialize();
}

Orbital::Orbital(int n, int l, int m, math::vec3 position)
    : m_Position(position), m_N{n}, m_L{l}, m_M{m} {
  assert(n > 0);
  assert(l >= 0 && l < n);
  assert(m >= -l && m <= l);
  initialize();
}

void Orbital::update(double deltaTime) {
}

std::shared_ptr<engine::Mesh> Orbital::getMesh() const {
  return m_Mesh;
}

void Orbital::initialize() {
  util::Timer& timer = util::Timer::getInstance();
  timer.startFunction();

  std::default_random_engine eng;

  // holds the highest value of probDensity
  double highestProb = 0;
  // the wave func is evaluated in a cube of side maxRadius * 2
  double maxRadius = math::estimateOrbitalRadius(m_N) * 3;
  // how much distance between one wave function eval and the next
  double step = maxRadius / 50.;
  // max amount of random offset (from the base position) of each sphere
  double maxSphereOffset = step * 0.7;
  // max amount of spheres in each step * step * step volume
  double maxSpheresPerVolume = 5;
  // size of spheres
  double sphereScale = step / 2.0;

  std::cout << "[orbital init params] - maxRadius: " << maxRadius << ", step: " << step
            << ", maxSphereOffset: " << maxSphereOffset << ", sphereScale: " << sphereScale
            << ", maxSpheresPerVolume: " << maxSpheresPerVolume << "\n";

  // evaluate wave function
  timer.start();
  math::WaveFunction waveFunc(m_N, m_L, m_M);
  for (double x = 0; x < maxRadius; x += step) {
    for (double y = -maxRadius; y < maxRadius; y += step) {
      for (double z = -maxRadius; z < maxRadius; z += step) {
        math::vec3 sphCoords = math::spherical(x, y, z);
        std::complex<double> psi = waveFunc(sphCoords[0], sphCoords[1], sphCoords[2]);
        std::complex<double> psiConj = std::conj(psi);
        ElectronPosition position = {
            .position = sphCoords,         //
            .probDensity = psi * psiConj,  //
            /*.probFlow = ,*/              //
            .spheres = 0                   //
        };
        if (position.probDensity.real() > highestProb) {
          highestProb = position.probDensity.real();
        }
        m_Positions.push_back(position);
      }
    }
  }
  timer.end("wave function evaluation");

  // determines how many spheres go in each position
  timer.start();
  std::uniform_real_distribution<double> sphereChanceDistribution;
  auto density = [](double x) { return 1 - std::exp(-11.0 * x); };
  unsigned spheresCount = 0;
  for (auto& pos : m_Positions) {
    pos.spheres = density(pos.probDensity.real() / highestProb) * maxSpheresPerVolume;
    spheresCount += pos.spheres;
  }
  timer.end("plot density evaluation");

  std::cout << "[orbital init params] - spheresCount: " << spheresCount << "\n";

  // init mesh
  timer.start();
  m_Mesh = engine::sphere(std::shared_ptr<engine::Material>(new engine::BasicMaterial),
                          spheresCount, 7, 4);
  timer.end("instantiating mesh");

  // initialize the position of each sphere
  // all transforms are pushed into a vector to be later collectivelly applied using
  // mesh->setTransforms instead of mesh->setTransform (just one opengl call instead of N)
  std::uniform_real_distribution<float> offsetDistribution(-maxSphereOffset, maxSphereOffset);

  std::vector<engine::Transform> transforms;

  timer.start();
  for (auto const& pos : m_Positions) {
    math::vec3 cartesianPosition = math::cartesian(pos.position);
    for (int i = 0; i < pos.spheres; i++) {
      transforms.push_back(
          engine::Transform()
              .setTranslation(cartesianPosition + math::vec3(offsetDistribution(eng),
                                                             offsetDistribution(eng),
                                                             offsetDistribution(eng)))
              .setScale(sphereScale));
    }
  }
  timer.end("creating sphere transforms");

  timer.start();
  m_Mesh->setTransforms(transforms);
  timer.end("sending transforms to GPU buffer");

  timer.endFunction("Orbital::initialize");
}

}  // namespace orbitals
