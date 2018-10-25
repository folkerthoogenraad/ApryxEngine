#pragma once

#include <memory>

#include "graphics/Surface.h"
#include "GLTexture.h"

namespace apryx {

	class GLGraphics2D;

	class GLSurface : public Surface, public std::enable_shared_from_this<GLSurface> {
		unsigned int m_Framebuffer;

		std::shared_ptr<GLTexture> m_DepthAttachment;
		std::shared_ptr<GLTexture> m_ColorAttachment;
		int m_Width;
		int m_Height;

		std::shared_ptr<GLGraphics2D> m_Graphics;
	public:
		GLSurface(int width, int height);
		~GLSurface();

		// Const is kinda misleading here, but oh well
		void bind() const;
		void unbind() const;

		int getWidth() const override { return m_Width; }
		int getHeight() const override { return m_Height; }

		std::shared_ptr<Texture> getTexture() const override { return m_ColorAttachment; }

		std::shared_ptr<GLTexture> getGLTexture() const { return m_ColorAttachment; }
		std::shared_ptr<GLTexture> getDepthTexture() const { return m_DepthAttachment; }

		virtual Graphics2D &getGraphics();
	};

}