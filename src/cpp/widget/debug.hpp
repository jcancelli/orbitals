#pragma once

#include "../math/vector.hpp"
#include "widget.hpp"

namespace orbitals {

namespace widget {

class DebugWidget : public Widget {
 public:
  DebugWidget();

 protected:
  void drawContent() override;
};

}  // namespace widget

}  // namespace orbitals
