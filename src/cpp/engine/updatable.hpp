#pragma once

namespace orbitals {

namespace engine {

class Updatable {
 public:
  virtual void update(double deltaTime){};
};

}  // namespace engine

}  // namespace orbitals
