#include "glDebug.hpp"

#include <GLES3/gl3.h>

#include <cassert>
#include <iostream>

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
              << functionCall << std::endl;
    noErrors = false;
  }
  assert(noErrors);
}

}  // namespace engine