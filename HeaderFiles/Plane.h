#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Light.h"
#include"Camera.h"

class Plane
{
public:
	//stores the main values of the pyamid
	glm::vec3 position;
	glm::mat4 model = glm::mat4(1.0f);
	Shader shader = Shader("default.vert", "default.frag");
	Texture texture = Texture("Default.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	VAO vao;
	VBO vbo;
	EBO ebo;
	GLfloat vertices[44] =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side 0
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side 1
		 0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side 2
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side 3
	};

	GLuint indices[6] =
	{
		0, 1, 3,
		0, 2, 3,
	};
	Light keyLight = Light(glm::vec3(2.5f, 2.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Light fillLight = Light(glm::vec3(2.5f, 2.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));;


	//constructors, used to define with and without a texture (without texture show default missing texture)
	Plane(glm::vec3 position, glm::vec3 scale, const char* texture, Light keyLight, Light fillLight);
	Plane(glm::vec3 position, glm::vec3 scale, Shader shader, Light keyLight, Light fillLight);

	void Rotate(float amount, glm::vec3 vector);
	void LinkAttrib();
	void AssignUniforms();
	void Build(Camera camera);
	void Delete();

};

#endif
