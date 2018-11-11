#pragma once

#include "graphics/Texture.h"

namespace apryx {

	class GLTexture : public Texture{
		unsigned int m_ID;

		int m_Width, m_Height;
		bool m_Flip = false;
	public:
		GLTexture();
		~GLTexture();

		void bind();
		void unbind();

		int getWidth() const override { return m_Width; }
		int getHeight() const override { return m_Height; }

		void setFiltering(TextureFiltering filtering) override;
		void setWrapping(WrappingMode wrapping) override;

		void setData(const Image &image) override;


		// RAW API. USE WITH CARE
		int getID() const { return m_ID; }
		bool isFlipped() const { return m_Flip; }
		void setFlipped(bool flip) { m_Flip = flip; }
		void setSize(int width, int height)  { m_Width = width; m_Height = height; }
	};

}