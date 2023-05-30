#include "frame_buffer.hpp"

#include <cassert>
#include <iostream>

#include "debug.hpp"

namespace orbitals {

namespace engine {

FrameBuffer::FrameBuffer() {
  glCall(glGenFramebuffers(1, &m_Id));
}

FrameBuffer::~FrameBuffer() {
  glCall(glDeleteFramebuffers(1, &m_Id));
}

void FrameBuffer::bind(Target target) const {
  glCall(glBindFramebuffer(target, m_Id));
}

void FrameBuffer::unbind(Target target) const {
  glCall(glBindFramebuffer(target, 0));
}

void FrameBuffer::checkIsComplete() const {
  glCall(GLenum status = glCheckFramebufferStatus(m_Id));
  switch (status) {
    case GL_FRAMEBUFFER_COMPLETE:
      return;
    case GL_FRAMEBUFFER_UNDEFINED:
      std::cout << "Frame buffer - Does not exist\n";
      assert(false);
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      std::cout << "Frame buffer - Incomplete attachments\n";
      assert(false);
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      std::cout << "Frame buffer - No valid attachments\n";
      assert(false);
    case GL_FRAMEBUFFER_UNSUPPORTED:
      std::cout << "Frame buffer - Combination of internal formats used by attachments results in "
                << "nonrenderable target\n";
      assert(false);
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
      std::cout << "Frame buffer - GL_RENDERBUFFER_SAMPLES is not the same for all attachments\n";
      assert(false);
    default:
      std::cout << "Unexpected return value for glCheckFramebufferStatus\n";
      assert(false);
  }
}

void FrameBuffer::setColorAttachment(RenderBuffer const& renderBuffer, unsigned index,
                                     Target target) const {
  bind(target);
  glCall(glFramebufferRenderbuffer(target, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER,
                                   renderBuffer.id()));
  unbind(target);
}

void FrameBuffer::setDepthAttachment(RenderBuffer const& renderBuffer, Target target) const {
  bind(target);
  glCall(
      glFramebufferRenderbuffer(target, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.id()));
  unbind(target);
}

void FrameBuffer::setStencilAttachment(RenderBuffer const& renderBuffer, Target target) const {
  bind(target);
  glCall(
      glFramebufferRenderbuffer(target, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.id()));
  unbind(target);
}

void FrameBuffer::setColorAttachment(Texture2D const& texture, unsigned index,
                                     Target target) const {
  bind(target);
  glCall(
      glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, texture.id(), 0));
  unbind(target);
}

void FrameBuffer::setDepthAttachment(Texture2D const& texture, Target target) const {
  bind(target);
  glCall(glFramebufferTexture2D(target, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.id(), 0));
  unbind(target);
}

void FrameBuffer::setStencilAttachment(Texture2D const& texture, Target target) const {
  bind(target);
  glCall(glFramebufferTexture2D(target, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.id(), 0));
  unbind(target);
}

}  // namespace engine

}  // namespace orbitals
