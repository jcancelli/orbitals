#pragma once

#include <iomanip>
#include <iostream>
#include <random>
#include <unordered_set>

#include "engine/camera_movement.hpp"
#include "engine/io/keyboard.hpp"
#include "engine/primitives/vertex.hpp"
#include "engine/scene.hpp"
#include "engine/shapes.hpp"
#include "math/bohr.hpp"
#include "math/coordinates.hpp"
#include "math/trigonometry.hpp"
#include "math/vector.hpp"
#include "math/wave_function.hpp"
#include "orbital.hpp"
#include "util/fs.hpp"

namespace orbitals {

using namespace orbitals::engine;
using namespace orbitals::math;

struct SampleScene : public Scene {
  std::shared_ptr<OrbitingCameraMovement> cameraMovement;
  std::shared_ptr<Orbital> orbital;

  SampleScene() {
    int n = 6, l = 2, m = 1;
    // int n = 1, l = 0, m = 0;
    double maxRadius = math::estimateOrbitalRadius(n) * 2.;

    m_Camera = std::shared_ptr<Camera>(
        new PerspectiveCamera(20, 0, 0, math::radians(45), Viewport::getInstance().aspectRatio()));
    m_Camera->setZFar(100000);
    // TODO: Set Z far to maxRadius * something
    cameraMovement =
        std::shared_ptr<OrbitingCameraMovement>(new OrbitingCameraMovement(m_Camera, vec3(0)));
    cameraMovement->setLimitPhi(false);
    cameraMovement->setMaxSpeedR(maxRadius / 3);
    cameraMovement->setPosition(math::estimateOrbitalRadius(n) * 4.0, M_PI_2, M_PI + M_PI_2);

    m_Light.setInvertedDirection(math::vec3(0, 1, 0));
    m_Light.setEffectedVolume(-maxRadius, maxRadius, -maxRadius, maxRadius, 0.1, 10000);

    orbital = std::shared_ptr<Orbital>(new Orbital(n, l, m));

    m_Meshes.push_back(orbital->getMesh());
  }

  void update(double deltaTime) override {
    for (auto const& downKey : Keyboard::getInstance().getDownKeys()) {
      switch (downKey) {
        case Key::ArrowUp:
          cameraMovement->moveUp();
          break;
        case Key::ArrowDown:
          cameraMovement->moveDown();
          break;
        case Key::ArrowLeft:
          cameraMovement->moveLeft();
          break;
        case Key::ArrowRight:
          cameraMovement->moveRight();
          break;
        case Key::Shift:
          cameraMovement->moveForward();
          break;
        case Key::Ctrl:
          cameraMovement->moveBack();
          break;
        default:
          // do nothing
          break;
      }
    }
    cameraMovement->update(deltaTime);
  }

  void handleEvents(std::vector<Event> events) override {
    for (Event const& event : events) {
      switch (event.type) {
        case Event::Type::Viewport:
          std::static_pointer_cast<PerspectiveCamera>(m_Camera)->setAspectRatio(
              event.viewport.width / event.viewport.height);
          break;
        case Event::Type::Wheel:
          if (event.wheel.deltaY < 0) {
            cameraMovement->moveForward();
          } else {
            cameraMovement->moveBack();
          }
          break;
        default:
          // noop
          break;
      }
    }
  }
};

}  // namespace orbitals
