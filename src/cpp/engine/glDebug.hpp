#pragma once

#include <string>

#ifdef DEBUG_MODE
#define glCall(glFunc) \
  clearGlErrors();     \
  glFunc;              \
  logGlErrors(__FILE__, #glFunc, __LINE__)
#else
#define glCall(glFunc) glFunc
#endif

namespace engine {

void clearGlErrors();
void logGlErrors(const std::string& file, const std::string& functionCall, int lineNumber);

}  // namespace engine