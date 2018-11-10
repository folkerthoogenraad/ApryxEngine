#include "Win32Context.h"

#include "opengl/GLTexture.h"
#include "opengl/GLSurface.h"

#include "console/Console.h"

#include "graphics/Sprite.h"
#include "graphics/FontUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_true_type.h"
#undef STB_TRUETYPE_IMPLEMENTATION

#include <fstream>
#include <string>
#include <streambuf>

namespace apryx {
	Win32Context::Win32Context(std::shared_ptr<Window> window)
		: m_Window(window)
	{
	}

	std::shared_ptr<Font> Win32Context::getDefaultFont()
	{
		if (m_DefaultFont == nullptr)
			m_DefaultFont = createDefaultFont(*this);

		return m_DefaultFont;
	}

	std::shared_ptr<Texture> Win32Context::createTexture()
	{
		return std::make_shared<GLTexture>();
	}

	std::shared_ptr<Texture> Win32Context::loadTexture(std::string path)
	{
		auto it = m_Textures.find(path);

		std::cout << path << std::endl;
		
		// Doesn't exist or is outdated
		if (it != m_Textures.end()) {
			auto shared = it->second.lock();
			
			if (shared) {
				return shared;
			}
		}

		Image image = loadImage(path);
		auto texture = createTexture();
		texture->setData(image);

		m_Textures[path] = texture;

		return texture;
	}

	std::shared_ptr<Font> Win32Context::loadFont(std::string path, int points)
	{
		auto resourcePair = std::make_pair(path, points);
		{
			auto it = m_Fonts.find(resourcePair);
			if (it != m_Fonts.end()) {
				auto sharedPtr = it->second.lock();

				if (sharedPtr != nullptr)
					return sharedPtr;
			}
		
		}

		// Load the file
		std::ifstream t(path, std::ifstream::binary);
		std::string str;

		// And allocate the right memory
		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		stbtt_fontinfo stFont;
		int ascent, descent;

		// Double loading right here, thats kinda stupid.
		// TODO render out the font the long way and not take the stupid shortcut with the 'BakeFontBitmap'.
		// TODO don't cut corners
		stbtt_InitFont(&stFont, (const unsigned char*)str.c_str(), stbtt_GetFontOffsetForIndex((const unsigned char*)str.c_str(), 0));

		float scale = stbtt_ScaleForPixelHeight(&stFont, points);
		stbtt_GetFontVMetrics(&stFont, &ascent, &descent, 0);
		float baseline = (int)((ascent) * scale);

		const int width = 512;
		const int height = 512;
		const int charStart = 32;
		const int charEnd = 126;
		const int charCount = charEnd - charStart;
		
		Image image(width, height);

		unsigned char temp_bitmap[width * height];
		stbtt_bakedchar cdata[charCount];

		// no guarantee this fits!
		stbtt_BakeFontBitmap(
			(const unsigned char*)str.c_str(), 
			0, points, temp_bitmap, width, height, charStart, charCount, cdata);

		auto texture = std::make_shared<GLTexture>();
		texture->setFiltering(GLTexture::TextureFiltering::Linear);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				auto n = temp_bitmap[x + y * width];
				Color32 c(255, 255, 255, n);
				image.setColor(x, y, c);
			}
		}

		texture->setData(image);
		
		auto font = std::make_shared<Font>();

		for (int i = 0; i < charCount; i++) {
			stbtt_bakedchar &bc = cdata[i];

			FontCharacter fc;
			fc.sprite = Sprite(texture, 
				(float)bc.x0, 
				(float)bc.y0, 
				(float)(bc.x1 - bc.x0), 
				(float)(bc.y1 - bc.y0));

			fc.xoffset = bc.xoff;
			fc.yoffset = bc.yoff + baseline;

			fc.xadvance = bc.xadvance;

			font->setCharacter((char)(i + charStart), fc);
		}

		font->setHeight(points);

		m_Fonts.insert_or_assign(resourcePair, font);

		return font;
	}

	Image Win32Context::loadImage(std::string path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(false);

		unsigned char *image = stbi_load(path.c_str(),
			&width,
			&height,
			&channels,
			STBI_rgb_alpha);

		if (image == nullptr) {
			Console::logError("Failed to load image");
			Console::logError(path);
			return Image::colored(1, 1, Color32::magenta());
		}
		if (channels != 4) {
			Console::logError("Image has to few components");
			Console::logError(path);

			return Image::colored(1, 1, Color32::magenta());
			stbi_image_free(image);
		}

		Image img(width, height);

		int index = 0;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				Color32 c = Color32::white();

				c.r = image[index + 0];
				c.g = image[index + 1];
				c.b = image[index + 2];
				c.a = image[index + 3];

				img.setColor(i, j, c);

				index += channels;
			}
		}

		stbi_image_free(image);

		return std::move(img);
	}
	
	std::shared_ptr<Surface> Win32Context::createSurface(int width, int height)
	{
		return std::make_shared<GLSurface>(width, height);
	}
}
