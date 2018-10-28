#include "GLSurface.h"

#include "graphics/Image.h"

#include "GL.h"
#include "GLGraphics2D.h"
#include "debug/Debug.h"

namespace apryx {
	GLSurface::GLSurface(int width, int height)
		:m_Width(width), m_Height(height), m_Graphics(nullptr)
	{
		m_ColorAttachment = std::make_shared<GLTexture>();
		m_DepthAttachment = std::make_shared<GLTexture>();

		glGenFramebuffers(1, &m_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

		m_ColorAttachment->bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		m_DepthAttachment->bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

		// Housekeeping. This should actually really not be here but yeah. It works good enough
		m_ColorAttachment->setSize(width, height);
		m_DepthAttachment->setSize(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->getID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment->getID(), 0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE) {
			Debug::logError("Failed to create frame buffer extention");
		}
	}

	GLSurface::~GLSurface()
	{
		glDeleteFramebuffers(1, &m_Framebuffer);
	}

	void GLSurface::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
	}

	void GLSurface::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLSurface::setData(const Image & image)
	{
		m_ColorAttachment->setData(image);

		if (image.getWidth() != m_Width || image.getHeight() != m_Height) {
			m_Width = image.getHeight();
			m_Height = image.getHeight();

			m_DepthAttachment->bind();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
		}
	}

	Graphics2D & GLSurface::getGraphics()
	{
		if (m_Graphics == nullptr) {
			auto t = shared_from_this();
			m_Graphics = std::make_shared<GLGraphics2D>(t);
		}
		return *m_Graphics;
	}
}
