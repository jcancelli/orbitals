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
#include "util/fs.hpp"

namespace orbitals {

using namespace orbitals::engine;
using namespace orbitals::math;

struct SampleMaterial : public Material {
  vec3 color;
  float shinyness;

  SampleMaterial(std::string const& shaderName, float r, float g, float b, float shinyness)
      : Material::Material(util::read_string(std::string("./shaders/") + shaderName + ".vert"),
                           util::read_string(std::string("./shaders/") + shaderName + ".frag")),
        color(r, g, b),
        shinyness(shinyness) {
  }

  void bind() override {
    m_Shader.bind();
    m_Shader.setUniform3f("uDiffuseColor", color);
    m_Shader.setUniform1f("uShinyness", shinyness);
  }

  void unbind() override {
    m_Shader.unbind();
  }
};

struct SampleScene : public Scene {
  std::shared_ptr<OrbitingCameraMovement> cameraMovement;

  SampleScene() {
    m_Camera = std::shared_ptr<Camera>(
        new PerspectiveCamera(20, 0, 0, math::radians(45), Viewport::getInstance().aspectRatio()));
    cameraMovement =
        std::shared_ptr<OrbitingCameraMovement>(new OrbitingCameraMovement(m_Camera, vec3(0)));

    m_Light.setEffectedVolume(-25, 25, -25, 25);

    std::shared_ptr<Material> sphereMaterial(
        new SampleMaterial("basic", 2. / 255., 70. / 255., 196. / 255., 2));

    int instances = 20000;
    std::shared_ptr<Mesh> sphere = engine::sphere(sphereMaterial, instances);

    m_Meshes.push_back(sphere);

    std::default_random_engine eng;
    std::normal_distribution<float> dist;
    for (int i = 0; i < instances; i++) {
      float x = dist(eng) * 25;
      float y = dist(eng) * 25;
      float z = dist(eng) * 25;
      sphere->setTransform(Transform().translate(x, y, z), i);
    }

    cameraMovement->setPosition(100, M_PI_2, M_PI);
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
