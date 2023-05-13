#include "clock.hpp"

namespace orbitals {

namespace engine {

void Clock::tick(double newElapsed) {
  m_Delta = newElapsed - m_Elapsed;
  m_Elapsed = newElapsed;
}

double Clock::delta() const {
  return m_Delta;
}

double Clock::elapsed() const {
  return m_Elapsed;
}

}  // namespace engine

}  // namespace orbitals
