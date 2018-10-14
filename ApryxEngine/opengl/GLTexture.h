#pragma once

#include "graphics/Texture.h"

namespace apryx {

	class GLTexture : public Texture{
		unsigned int m_ID;
	public:
		enum WrappingMode {
			Clamp,
			Repeat
		};
		enum TextureFiltering {
			Linear,
			NearestNeighbour
		};

		float m_Width, m_Height;
	public:
		GLTexture();
		~GLTexture();

		void bind();
		void unbind();

		float getWidth() const override { return m_Width; }
		float getHeight() const override { return m_Height; }

		void setFiltering(TextureFiltering filtering);
		void setWrapping(WrappingMode wrapping);

		// TODO use some caching or something to find the correct width and height yafeelme
		void setData(const Image &image) override;
	};

}