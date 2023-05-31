#pragma once

#include "../math/vector.hpp"

namespace orbitals {

namespace engine {

struct Light {
  math::vec3 color = math::vec3(1, 1, 1);
};

struct DirectionalLight : public Light {
  math::vec3 invertedDirection;
};

}  // namespace engine

}  // namespace orbitals
