#pragma once

#include <memory>

#include "material.hpp"
#include "mesh.hpp"

namespace orbitals {

namespace engine {

std::shared_ptr<Mesh> sphere(std::shared_ptr<Material> material, unsigned instancesCount = 1);

std::shared_ptr<Mesh> cube(std::shared_ptr<Material> material, unsigned instancesCount = 1);

}  // namespace engine

}  // namespace orbitals
