#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

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

class Cube
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
	GLfloat vertices[264] =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side 0
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side 1
		 0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side 2
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side 3
								
		-0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,     -1.0f, 0.0f, 0.0f, // Left Side 4
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,     -1.0f, 0.0f, 0.0f, // Left Side 5
		-0.5f, 0.5f, 0.5f,	    0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,     -1.0f, 0.0f, 0.0f, // Left Side 6
		-0.5f, 0.5f, -0.5f, 	0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,     -1.0f, 0.0f, 0.0f, // Left Side 7
								
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,      0.0f, 0.0f, -1.0f, // Facing side 8
 		 0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      0.0f, 0.0f, -1.0f, // Facing side 9
		-0.5f, 0.5f,  -0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      0.0f, 0.0f, -1.0f, // Facing side 10
		 0.5f, 0.5f,  -0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      0.0f, 0.0f, -1.0f, // Facing side 11

		 0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,      1.0f, 0.0f,  0.0f, // Right side 12
		 0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      1.0f, 0.0f,  0.0f, // Right side 13
		 0.5f, 0.5f,  -0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      1.0f, 0.0f,  0.0f, // Right side 14 
		 0.5f, 0.5f,   0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      1.0f, 0.0f,  0.0f, // Right side 15
									
		 0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 0.0f,      0.0f, 0.0f,  1.0f, // Non-facing side 16
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      0.0f, 0.0f,  1.0f, // Non-facing side 17
		 0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      0.0f, 0.0f,  1.0f, // Non-facing side 18
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      0.0f, 0.0f,  1.0f, // Non-facing side 19

		-0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 0.0f, 	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Top side 20
		-0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Top side 21
		 0.5f, 0.5f, -0.5f,    0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      0.0f, 1.0f, 0.0f, // Top side 22
		 0.5f, 0.5f,  0.5f,    0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      0.0f, 1.0f, 0.0f  // Top side 23
	};

	GLuint indices[36] =
	{
		0, 1, 3,
		0, 2, 3,
		4, 5, 7,
		4, 6, 7,
		8, 9, 11,
		8, 10, 11,
		12, 13, 15,
		12, 14, 15,
		16, 17, 19,
		16, 18, 19,
		20, 21, 23,
		20, 22, 23
	};
	Light keyLight = Light(glm::vec3(2.5f, 2.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Light fillLight = Light(glm::vec3(2.5f, 2.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));;


	//constructors, used to define with and without a texture (without texture show default missing texture)
	Cube(glm::vec3 position, glm::vec3 scale, const char* texture, Light keyLight, Light fillLight);
	Cube(glm::vec3 position, glm::vec3 scale, Shader shader, Light keyLight, Light fillLight);

	void Rotate(float amount, glm::vec3 vector);
	void LinkAttrib();
	void AssignUniforms();
	void Build(Camera camera);
	void Delete();

};

#endif
