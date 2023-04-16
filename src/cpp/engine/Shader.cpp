#include "Shader.hpp"

#include <cassert>
#include <iostream>

#include "glDebug.hpp"

static GLuint compileShader(char const* src, GLenum shaderType) {
  const GLuint id = glCall(glCreateShader(shaderType));
  glCall(glShaderSource(id, 1, &src, NULL));
  glCall(glCompileShader(id));
  GLint compileStatus;
  glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus));
  if (compileStatus == GL_FALSE) {
    GLsizei errorLength;
    glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorLength));
    GLchar errorMessage[errorLength];
    glCall(glGetShaderInfoLog(id, errorLength, NULL, errorMessage));
    std::cout << "[WebGL error] Error while compiling "
              << ((shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment")
              << " shader: " << errorMessage << std::endl;
    assert(false);
  }
}

namespace engine {
Shader::Shader(std::string const& vertSrc, std::string const& fragSrc) {
  m_Id = glCall(glCreateProgram());

  m_VertId = compileShader(vertSrc.c_str(), GL_VERTEX_SHADER);
  m_FragId = compileShader(fragSrc.c_str(), GL_FRAGMENT_SHADER);

  glCall(glAttachShader(m_Id, m_VertId));
  glCall(glAttachShader(m_Id, m_FragId));

  glCall(glLinkProgram(m_Id));
  GLint linkStatus;
  glCall(glGetProgramiv(m_Id, GL_LINK_STATUS, &linkStatus));
  if (linkStatus == GL_FALSE) {
    GLsizei errorLength;
    glCall(glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &errorLength));
    GLchar errorMessage[errorLength];
    glCall(glGetProgramInfoLog(m_Id, errorLength, NULL, errorMessage));
    std::cout << "[WebGL error] Error while linking shader: " << errorMessage << std::endl;
    assert(false);
  }
}

Shader::~Shader() {
  glCall(glDeleteProgram(m_Id));
}

void Shader::bind() const {
  glCall(glUseProgram(m_Id));
}

void Shader::unbind() const {
  glCall(glUseProgram(0));
}

GLuint Shader::id() const {
  return m_Id;
}

}  // namespace engine