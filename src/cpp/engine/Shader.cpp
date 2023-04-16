#include "Shader.hpp"

#include <cassert>
#include <iostream>

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

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
  return id;
}

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

void Shader::setUniform1f(std::string const& key, GLfloat v0) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform1f(uniformLocation, v0));
}

void Shader::setUniform2f(std::string const& key, GLfloat v0, GLfloat v1) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform2f(uniformLocation, v0, v1));
}

void Shader::setUniform2f(std::string const& key, math::vec2 const& v) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform2f(uniformLocation, v[0], v[1]));
}

void Shader::setUniform3f(std::string const& key, GLfloat v0, GLfloat v1, GLfloat v2) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform3f(uniformLocation, v0, v1, v2));
}

void Shader::setUniform3f(std::string const& key, math::vec3 const& v) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform3f(uniformLocation, v[0], v[1], v[2]));
}

void Shader::setUniform4f(std::string const& key, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform4f(uniformLocation, v0, v1, v2, v3));
}

void Shader::setUniform4f(std::string const& key, math::vec4 const& v) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniform4f(uniformLocation, v[0], v[1], v[2], v[3]));
}

void Shader::setUniformMat4(std::string const& key, math::mat4 const& m) {
  GLuint uniformLocation = getUniformLocation(key);
  if (uniformLocation == -1) {
    return;
  }
  glCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &m[0][0]));
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

GLuint Shader::getUniformLocation(std::string const& key) {
  auto search = m_UniformLocationCache.find(key);
  if (search != m_UniformLocationCache.end()) {
    return search->second;
  }
  glCall(GLuint uniformLocation = glGetUniformLocation(m_Id, key.c_str()));
  if (uniformLocation == -1) {
    // If an uniform is unused (inside a shader code), it is removed.
    // Therefore glGetUniformLocation could return -1 even if the uniform is actually present.
    std::cout << "[WebGL error] Could not find uniform \"" << key << "\" location." << std::endl;
  }
  m_UniformLocationCache[key] = uniformLocation;
  return uniformLocation;
}

}  // namespace engine

}  // namespace orbitals