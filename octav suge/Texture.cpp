#include "Texture.h"

#include"stbimage/stb_image.h"


Textur::Textur(const std::string& path)
	:m_renderid(0), m_filepath(path), m_localbuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localbuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (m_localbuffer == NULL) {
		std::cout << "not find";
	}
	glGenTextures(1, &m_renderid);
	glBindTexture(GL_TEXTURE_2D, m_renderid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_localbuffer)
		stbi_image_free(m_localbuffer);
}

Textur::~Textur()
{
	glDeleteTextures(1, &m_renderid);
}

void Textur::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderid);
}

void Textur::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
