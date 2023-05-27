#pragma once

#include <string>

#ifdef DEBUG_MODE
#define glCall(glFunc)               \
  orbitals::engine::clearGlErrors(); \
  glFunc;                            \
  orbitals::engine::logGlErrors(__FILE__, #glFunc, __LINE__)
#else
#define glCall(glFunc) glFunc
#endif

namespace orbitals {

namespace engine {

void clearGlErrors();
void logGlErrors(const std::string& file, const std::string& functionCall, int lineNumber);

}  // namespace engine

}  // namespace orbitals