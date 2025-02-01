#include "Texture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

unsigned int Texture::genTexture(const char* texName) {

	int width, height, nrChannels; // Integers representing the width, height, and number of channels in the image
	unsigned char* data = stbi_load(texName, &width, &height, &nrChannels, 0); // Returns image data and sets the width and height and number of channels

	unsigned int texture; // OpenGL ID
	//unsigned int texture2;

	glGenTextures(1, &texture); // Returns ID

	glActiveTexture(GL_TEXTURE0); // activate texture unit first
	glBindTexture(GL_TEXTURE_2D, texture); // Binds the texture to the context

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//data = stbi_load("texture.JPG", &width, &height, &nrChannels, 0);

	if (data && nrChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (data && nrChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return texture;
}