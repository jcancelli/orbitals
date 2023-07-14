#include "performance.hpp"

#include <iostream>

namespace orbitals {

namespace util {

Timer Timer::s_Instance = Timer();

Timer::Timer()
    : m_StartTimeFunction(std::chrono::system_clock::now()),
      m_StartTime(std::chrono::system_clock::now()) {
}

Timer& Timer::getInstance() {
  return s_Instance;
}

void Timer::startFunction() {
  m_StartTimeFunction = std::chrono::system_clock::now();
}

void Timer::endFunction(std::string const& functionName) {
  using namespace std::chrono;
  const auto endTime = system_clock::now();
  const auto ms = duration_cast<milliseconds>(endTime - m_StartTimeFunction).count();
  std::cout << "[timer] [function] - " << functionName << " - " << ms << "ms\n";
}

void Timer::start() {
  m_StartTime = std::chrono::system_clock::now();
}

void Timer::end(std::string const& message) {
  using namespace std::chrono;
  const auto endTime = system_clock::now();
  const auto ms = duration_cast<milliseconds>(endTime - m_StartTime).count();
  std::cout << "[timer] - " << message << " - " << ms << "ms\n";
}

}  // namespace util

}  // namespace orbitals
