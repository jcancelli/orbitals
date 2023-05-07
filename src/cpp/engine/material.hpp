#pragma once

namespace orbitals {

namespace engine {

class Material {
 public:
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
};

}  // namespace engine

}  // namespace orbitals
