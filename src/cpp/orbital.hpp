#pragma once

#include <complex>
#include <memory>
#include <vector>

#include "engine/mesh.hpp"
#include "math/vector.hpp"

namespace orbitals {

struct ElectronPosition {
  math::vec3 position;
  std::complex<double> probDensity;
  std::complex<double> probFlow;
  int spheres;
};

class Orbital {
 private:
  math::vec3 m_Position;
  int m_N, m_L, m_M;
  std::vector<ElectronPosition> m_Positions;
  std::shared_ptr<engine::Mesh> m_Mesh;

 public:
  Orbital();
  Orbital(int n, int l, int m, math::vec3 position = math::vec3(0, 0, 0));
  void update(double deltaTime);
  std::shared_ptr<engine::Mesh> getMesh() const;

 private:
  void initialize();
};

}  // namespace orbitals
