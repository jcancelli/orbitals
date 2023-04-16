#pragma once

#include <GLES3/gl3.h>

#include <string>
#include <unordered_map>

#include "../math/matrix.hpp"

namespace orbitals {

namespace engine {

class Shader {
 private:
  GLuint m_Id;
  GLuint m_VertId;
  GLuint m_FragId;
  std::unordered_map<std::string, GLuint> m_UniformLocationCache;

 public:
  Shader(std::string const& vertSrc, std::string const& fragSrc);
  ~Shader();
  void setUniform1f(std::string const& key, GLfloat v0);
  void setUniform2f(std::string const& key, GLfloat v0, GLfloat v1);
  void setUniform2f(std::string const& key, math::vec2 const& v);
  void setUniform3f(std::string const& key, GLfloat v0, GLfloat v1, GLfloat v2);
  void setUniform3f(std::string const& key, math::vec3 const& v);
  void setUniform4f(std::string const& key, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
  void setUniform4f(std::string const& key, math::vec4 const& v);
  void setUniformMat4(std::string const& key, math::mat4 const& m);
  void bind() const;
  void unbind() const;
  GLuint id() const;

 private:
  GLuint getUniformLocation(std::string const& key);
};

}  // namespace engine

}  // namespace orbitals