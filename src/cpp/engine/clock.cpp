#include "clock.hpp"

namespace orbitals {

namespace engine {

void Clock::tick(double newElapsed) {
  m_Delta = newElapsed - m_Elapsed;
  m_Elapsed = newElapsed;
  m_OnTickListeners.notify(*this);
}

double Clock::delta() const {
  return m_Delta;
}

double Clock::elapsed() const {
  return m_Elapsed;
}

unsigned Clock::addOnTickListener(util::Listeners<Clock const&>::Listener const& listener) {
  return m_OnTickListeners.add(listener);
}

void Clock::removeOnTickListener(unsigned listenerID) {
  m_OnTickListeners.remove(listenerID);
}

}  // namespace engine

}  // namespace orbitals
