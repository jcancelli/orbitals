#pragma once

#include "../math/vector.hpp"
#include "../util/listeners_manager.hpp"
#include "widget.hpp"

namespace orbitals {

namespace widget {

class OrbitalWidget : public Widget {
 public:
  using ApplyListener = util::Listeners<int, int, int, math::vec3>::Listener;

 private:
  int m_N, m_L, m_M;
  math::vec3 m_Color;
  util::Listeners<int, int, int, math::vec3> m_ApplyPressedListeners;

 public:
  OrbitalWidget();
  OrbitalWidget(int n, int l, int m);
  unsigned addOnApplyPressedListener(ApplyListener listener);
  void removeOnApplyPressedListener(unsigned listenerID);
  void setN(int n);
  int getN() const;
  void setL(int l);
  int getL() const;
  void setM(int m);
  int getM() const;
  void setColor(math::vec3 const& color);
  math::vec3 getColor() const;

 protected:
  void drawContent() override;

 private:
  void keepNumbersInBouds();
};

}  // namespace widget

}  // namespace orbitals
