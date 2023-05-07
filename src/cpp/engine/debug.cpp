#include "debug.hpp"

#include <GLES3/gl3.h>

#include <cassert>
#include <iostream>

namespace orbitals {

namespace engine {

void clearGlErrors() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

void logGlErrors(const std::string& file, const std::string& functionCall, int lineNumber) {
  GLenum errorCode;
  bool noErrors = true;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::cout << "[WebGL error] (" << errorCode << ") @ " << file << ":" << lineNumber << " => "
              << functionCall << "\n";
    noErrors = false;
  }
  assert(noErrors);
}

}  // namespace engine

}  // namespace orbitals