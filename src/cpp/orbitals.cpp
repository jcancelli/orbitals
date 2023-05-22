#include <emscripten/bind.h>

#include <memory>

#include "engine/application.hpp"
#include "sample_scene.hpp"

namespace orbitals {

class Orbitals : public engine::Application {
 public:
  Orbitals(std::string const& canvasID) : Application::Application(canvasID) {
    setScene(std::shared_ptr<SampleScene>(new SampleScene));
  }
};

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals, emscripten::base<engine::Application>>("Orbitals")
      .constructor<std::string>();
}

}  // namespace orbitals
