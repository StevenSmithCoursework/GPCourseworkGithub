#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>


Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	//Loads texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed: " << fileName << std::endl;
	}

	//Creates the texture and tells OpenGL to treat it as a texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Controls what happens when the object is outwith the texture width or height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Controls how the texture is inter/extrapolated
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Sends texture to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//Deletes texture data from GPU
	stbi_image_free(imageData);
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::BindTexture(unsigned int unit)
{
	//Ensure the unit is within range for OpenGL
	assert(unit >= 0 && unit <= 31);

	//Sets active texture unit and binds the texture
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
