#pragma once

#include "gl_object.hpp"
#include "render_buffer.hpp"
#include "texture.hpp"

namespace orbitals {

namespace engine {

class FrameBuffer : public GLObject {
 public:
  enum Target { Default = GL_FRAMEBUFFER, Read = GL_READ_FRAMEBUFFER, Draw = GL_DRAW_FRAMEBUFFER };

 public:
  FrameBuffer();
  ~FrameBuffer();
  void bind(Target target = Default) const;
  void unbind(Target target = Default) const;
  void checkIsComplete(Target target = Default) const;
  void setColorAttachment(RenderBuffer const& renderBuffer, unsigned index = 0,
                          Target target = Default) const;
  void setDepthAttachment(RenderBuffer const& renderBuffe, Target target = Default) const;
  void setStencilAttachment(RenderBuffer const& renderBuffer, Target target = Default) const;
  void setColorAttachment(Texture2D const& texture, unsigned index = 0,
                          Target target = Default) const;
  void setDepthAttachment(Texture2D const& texture, Target target = Default) const;
  void setStencilAttachment(Texture2D const& texture, Target target = Default) const;
};

}  // namespace engine

}  // namespace orbitals
