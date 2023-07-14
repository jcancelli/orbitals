#pragma once

#include <chrono>
#include <string>

namespace orbitals {

namespace util {

class Timer {
 private:
  std::chrono::time_point<std::chrono::system_clock> m_StartTimeFunction, m_StartTime;
  static Timer s_Instance;

 private:
  Timer();

 public:
  static Timer& getInstance();
  void startFunction();
  void endFunction(std::string const& message);
  void start();
  void end(std::string const& message);
};

}  // namespace util

}  // namespace orbitals
