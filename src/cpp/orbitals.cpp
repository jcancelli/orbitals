#include <emscripten/bind.h>

#include <memory>

#include "engine/application.hpp"
#include "sample_scene.hpp"
#include "widget/debug.hpp"
#include "widget/orbital.hpp"

namespace orbitals {

class Orbitals : public engine::Application {
  widget::OrbitalWidget orbitalWidget;
  widget::DebugWidget debugWidget;

 public:
  Orbitals() {
    setScene(std::shared_ptr<SampleScene>(new SampleScene));
  }

  void onUpdate() override {
    debugWidget.draw();
    orbitalWidget.draw();
  }
};

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals, emscripten::base<engine::Application>>("Orbitals").constructor();
}

}  // namespace orbitals
