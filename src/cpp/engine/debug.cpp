#include "debug.hpp"

#include <GLES3/gl3.h>

#include <cassert>
#include <iostream>

namespace orbitals {

namespace engine {

static std::string errorCodeToString(GLenum errorCode) {
  switch (errorCode) {
    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";
    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default:
      return std::string("UNKNOWN_ERROR: ") + std::to_string(errorCode);
  }
}

void clearGlErrors() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

void logGlErrors(const std::string& file, const std::string& functionCall, int lineNumber) {
  GLenum errorCode;
  bool noErrors = true;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::cout << "[WebGL error] (" << errorCodeToString(errorCode) << ") @ " << file << ":"
              << lineNumber << " => " << functionCall << "\n";
    noErrors = false;
  }
  assert(noErrors);
}

}  // namespace engine

}  // namespace orbitals