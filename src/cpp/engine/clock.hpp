#pragma once

namespace orbitals {

namespace engine {

class Clock {
 private:
  double m_Elapsed;
  double m_Delta;

 public:
  void tick(double newElapsed);
  double delta() const;
  double elapsed() const;
};

}  // namespace engine

}  // namespace orbitals
