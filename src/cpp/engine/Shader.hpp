#pragma once

#include <GLES3/gl3.h>

#include <string>

namespace engine {

class Shader {
 private:
  GLuint m_Id;
  GLuint m_VertId;
  GLuint m_FragId;

 public:
  Shader(std::string const& vertSrc, std::string const& fragSrc);
  ~Shader();
  void bind() const;
  void unbind() const;
  GLuint id() const;
};

}  // namespace engine