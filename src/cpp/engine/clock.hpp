#pragma once

#include "../util/listeners_manager.hpp"

namespace orbitals {

namespace engine {

class Clock {
 private:
  double m_Elapsed;
  double m_Delta;
  util::Listeners<Clock const&> m_OnTickListeners;

 public:
  void tick(double newElapsed);
  double delta() const;
  double elapsed() const;
  unsigned addOnTickListener(util::Listeners<Clock const&>::Listener const& listener);
  void removeOnTickListener(unsigned listenerID);
};

}  // namespace engine

}  // namespace orbitals
