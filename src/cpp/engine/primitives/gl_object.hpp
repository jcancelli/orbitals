#pragma once

#include <GLES3/gl3.h>

namespace orbitals {

namespace engine {

class GLObject {
 protected:
  GLuint m_Id;

 public:
  GLuint id() const;
};

}  // namespace engine

}  // namespace orbitals
