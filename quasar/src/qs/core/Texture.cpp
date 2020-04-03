///
/// Texture.cpp
/// quasar
///
/// Apache 2.0 LICENSE.
/// Refer to LICENSE.txt for more details.
///

#include <array>

#include <glad/glad.h>
#include <stb_image.h>

#include "qs/utils/Error.hpp"

#include "Texture.hpp"

///
/// Core namespace.
///
namespace qs
{
	Texture::Texture() noexcept
		:m_id(0), m_width(0), m_height(0)
	{
		std::string msg = "You have created a default texture object. Remember to call load()!";
		qs::Error::handle().callback("Texture.cpp", 27, msg);
	}

	Texture::Texture(const std::string& file, unsigned int mipmapLevel)
		:m_id(0), m_width(0), m_height(0)
	{
		load(file, mipmapLevel);
	}

	Texture::Texture(const unsigned char* mem, const unsigned int size, unsigned int mipmapLevel)
		: m_id(0), m_width(0), m_height(0)
	{
		load(mem, size, mipmapLevel);
	}

	Texture::~Texture() noexcept
	{
		unbind();
		glDeleteTextures(1, &m_id);
	}

	void Texture::load(const std::string& file, unsigned int mipmapLevel)
	{
		// Generate texture in OpenGL and bind to 2D texture.
		glGenTextures(1, &m_id);
		bind();

		unsigned char* data = stbi_load(file.c_str(), &m_width, &m_height, nullptr, STBI_rgb_alpha);

		if (data)
		{
			// Gen texture into OpenGL.
			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGBA16, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			// Set filtering. When minimizing texture, linear interpolate, else nearest for nice pixel 2d art look.
			setMinifyFilter(qs::Texture::Filter::LINEAR_MIPMAP_LINEAR);

			// Set interpolation for mipmapping.
			setMagnifyFilter(qs::Texture::Filter::NEAREST);

			// Default clamp to edge.
			clampToEdge();
		}
		else
		{
			std::string msg = "Failed to load texture: " + file + " Reason: " + stbi_failure_reason();
			qs::Error::handle().callback("Texture.cpp", 66, msg);
		}

		stbi_image_free(data);
	}

	void Texture::load(const unsigned char* mem, const unsigned int size, unsigned int mipmapLevel)
	{
		// Generate texture in OpenGL and bind to 2D texture.
		glGenTextures(1, &m_id);
		bind();

		unsigned char* data = stbi_load_from_memory(mem, size, &m_width, &m_height, nullptr, STBI_rgb_alpha);

		if (data)
		{
			// Gen texture into OpenGL.
			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGBA16, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			// Set filtering. When minimizing texture, linear interpolate, else nearest for nice pixel 2d art look.
			setMinifyFilter(qs::Texture::Filter::LINEAR_MIPMAP_LINEAR);

			// Set interpolation for mipmapping.
			setMagnifyFilter(qs::Texture::Filter::NEAREST);

			// Default clamp to edge.
			clampToEdge();
		}
		else
		{
			std::string msg = "Failed to load texture: " + file + " Reason: " + stbi_failure_reason();
			qs::Error::handle().callback("Texture.cpp", 66, msg);
		}

		stbi_image_free(data);
	}

	void Texture::bind() noexcept
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind() noexcept
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::setRepeated() noexcept
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void Texture::setMirrored() noexcept
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}

	void Texture::clampToEdge() noexcept
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	void Texture::clampToBorder(protostar::Colour& border) noexcept
	{
		bind();
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border.asFloats().data());
	}

	void Texture::setMinifyFilter(const qs::Texture::Filter& filter)
	{
		bind();
		if (filter == qs::Texture::Filter::LINEAR)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else if (filter == qs::Texture::Filter::NEAREST)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	}

	void Texture::setMagnifyFilter(const qs::Texture::Filter& filter)
	{
		bind();
		if (filter == qs::Texture::Filter::LINEAR)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else if (filter == qs::Texture::Filter::NEAREST)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	}

	const int Texture::getWidth() const noexcept
	{
		return m_width;
	}

	const int Texture::getHeight() const noexcept
	{
		return m_height;
	}
}