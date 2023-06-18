#pragma once

#include <iomanip>
#include <iostream>
#include <random>
#include <unordered_set>

#include "engine/camera_movement.hpp"
#include "engine/io/keyboard.hpp"
#include "engine/primitives/vertex.hpp"
#include "engine/scene.hpp"
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

struct Sphere {
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;

  Sphere(unsigned meridians = 20, unsigned parallels = 20, unsigned instances = 1) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    double r = 0.5;
    double phiStep = (M_PI * 2) / meridians;
    double thetaStep = M_PI / parallels;

    // set vertices
    vertices.push_back(Vertex(cartesian(r, 0, 0)));
    for (double theta = thetaStep; theta < M_PI; theta += thetaStep) {
      for (double phi = 0; phi < M_PI * 2; phi += phiStep) {
        vertices.push_back(Vertex(cartesian(r, theta, phi)));
      }
    }
    vertices.push_back(Vertex(cartesian(r, M_PI, 0)));

    int faces = 0;
    // set indices
    for (int i = 1; i < meridians; i++) {
      indices.push_back(0);
      indices.push_back(i);
      indices.push_back(i + 1);
    }
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(meridians);

    for (int parallel = 0; parallel < parallels - 2; parallel++) {
      for (int meridian = 0; meridian < meridians; meridian++) {
        indices.push_back(parallel * parallels + meridian);
        indices.push_back(parallel * parallels + meridian + parallels);
        indices.push_back(parallel * parallels + meridian + 1);
        indices.push_back(parallel * parallels + meridian + 1);
        indices.push_back(parallel * parallels + meridian + parallels);
        indices.push_back(parallel * parallels + meridian + parallels + 1);
      }
    }

    const int lastIndex = vertices.size() - 1;
    for (int i = lastIndex - meridians; i < lastIndex - 1; i++) {
      indices.push_back(i);
      indices.push_back(i + 1);
      indices.push_back(lastIndex);
    }
    indices.push_back(lastIndex - meridians);
    indices.push_back(lastIndex - 1);
    indices.push_back(lastIndex);

    material = std::shared_ptr<Material>(new SampleMaterial("basic", 0, 0, 0, 8));
    mesh = std::shared_ptr<Mesh>(new Mesh(vertices, indices, material, instances));
  }
};

struct Cube {
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;

  Cube(unsigned instances = 1) {
    std::vector<Vertex> vertices{
        Vertex(-0.5, -0.5, -0.5), Vertex(-0.5, 0.5, -0.5),  // left front 	0 1
        Vertex(0.5, -0.5, -0.5),  Vertex(0.5, 0.5, -0.5),   // right front  2 3
        Vertex(-0.5, -0.5, 0.5),  Vertex(-0.5, 0.5, 0.5),   // left back	4 5
        Vertex(0.5, -0.5, 0.5),   Vertex(0.5, 0.5, 0.5),    // right back	6 7
    };                                                      //
    std::vector<GLuint> indices{
        0, 2, 3, 0, 3, 1,                                   //
        2, 6, 3, 6, 3, 7,                                   //
        0, 4, 1, 4, 1, 5,                                   //
        6, 4, 7, 4, 7, 5,                                   //
        1, 3, 5, 3, 5, 7,                                   //
        0, 2, 4, 2, 4, 6                                    //
    };                                                      //
    material = std::shared_ptr<Material>(new SampleMaterial("basic", 0, 0, 0, 8));
    mesh = std::shared_ptr<Mesh>(new Mesh(vertices, indices, material, instances));
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

    int instances = 20000;
    Sphere sphere(20, 20, instances);
    SampleMaterial* spheresMaterial = (SampleMaterial*)sphere.material.get();
    spheresMaterial->color = vec3(2. / 255., 70. / 255., 196. / 255.);
    spheresMaterial->shinyness = 2;
    m_Meshes.push_back(sphere.mesh);

    std::default_random_engine eng;
    std::normal_distribution<float> dist;
    for (int i = 0; i < instances; i++) {
      float x = dist(eng) * 25;
      float y = dist(eng) * 25;
      float z = dist(eng) * 25;
      sphere.mesh->setTransform(Transform().translate(x, y, z), i);
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
