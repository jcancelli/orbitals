#include "render_buffer.hpp"

#include <cassert>

#include "debug.hpp"

namespace orbitals {

namespace engine {

RenderBuffer::RenderBuffer(GLsizei width, GLsizei height, GLenum internalFormat, GLsizei samples) {
  GLint maxRenderBufferSize;
  glCall(glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderBufferSize));
  assert(width > 0 && width <= maxRenderBufferSize);
  assert(height > 0 && height <= maxRenderBufferSize);
  assert(samples >= 0);
  glCall(glGenRenderbuffers(1, &m_Id));
  bind();
  glCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, width, height));
  unbind();
}

RenderBuffer::~RenderBuffer() {
  glCall(glDeleteRenderbuffers(1, &m_Id));
}

void RenderBuffer::bind() const {
  glCall(glBindRenderbuffer(GL_RENDERBUFFER, m_Id));
}

void RenderBuffer::unbind() const {
  glCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

}  // namespace engine

}  // namespace orbitals
