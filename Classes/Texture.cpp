#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType; 

	// Stores the Dimensions of the image and the color channels of the image
	int widthImg, heightImg, numColCh;
	// Flip the image for correct oriantation
	stbi_set_flip_vertically_on_load(true);
	// Read the image from the file and store as bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assign the texture to the texture object
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to minimize and magnify the texture
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the type of algrothrim that is used to wrap the texture
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra code for GL_CLAMP_TO_BOARDER usage
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0g};
	// glTexParameterfv(texType, GL_TEXTURE_BORDER_COLOR, flatColor);


	// Assignes the image to the OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the texture Object
	stbi_image_free(bytes);
	// Unbinds the OpenGL Texture object so that it cant accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);

}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}