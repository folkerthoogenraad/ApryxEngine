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

		int m_Width, m_Height;
		bool m_Flip = false;
	public:
		GLTexture();
		~GLTexture();

		void bind();
		void unbind();

		int getWidth() const override { return m_Width; }
		int getHeight() const override { return m_Height; }

		void setFiltering(TextureFiltering filtering);
		void setWrapping(WrappingMode wrapping);

		void setData(const Image &image) override;


		// RAW API. USE WITH CARE
		int getID() const { return m_ID; }
		bool isFlipped() const { return m_Flip; }
		void setFlipped(bool flip) { m_Flip = flip; }
		void setSize(float width, float height)  { m_Width = width; m_Height = height; }
	};

}