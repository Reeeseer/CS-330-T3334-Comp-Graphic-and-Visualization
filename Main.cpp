#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Pyramid.h"
#include"Light.h"
#include"Cube.h"
#include"Plane.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	//These are parent positons of comples shapes to allow for movement of complex shapes with ease rather than moving each piece one by one
	glm::vec3 pencilCupPosition = glm::vec3(7.5f, -0.5f, -15.0f);					//cup that holds pencils
	glm::vec3 pencilPosition = pencilCupPosition + glm::vec3(-0.25f, 0.5f, -0.0f);	//the pencils positions
	glm::vec3 bookStackPosition = glm::vec3(-8.0f, -0.95f, -8.0f);					//the stack of books position
	glm::vec3 computerPosition = glm::vec3(0.0f, -0.0f, -10.0f);					//position of the computer

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 3.0f, 10.0f));

	Light keyLight(computerPosition + glm::vec3(-5.0f, 8.0f, -4.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Light fillLight(glm::vec3(-2.0f, 0.0f, -5.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	// These vectors handle the building and assignment of each shape type to make object generation streamline, just add the object the the correct vector
	std::vector<Cube> cubeList;
	std::vector<Pyramid> pyramidList;
	
	Plane table(glm::vec3(0.0f, -1.2f, -5.0f), glm::vec3(50.0f, 0.0f, 50.0f), "Table.png", keyLight, fillLight);

	//Pencil 1 Objects
	Pyramid pencilTop(pencilPosition + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "Pencil Top.png", keyLight, fillLight);
	pyramidList.push_back(pencilTop);
	Cube pencilBody(pencilPosition + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 2.0f, 0.2f), "Pencil Body.png", keyLight, fillLight);
	cubeList.push_back(pencilBody);
	Cube pencilEraser(pencilPosition + glm::vec3(0.0f, -1.1f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "Eraser.png", keyLight, fillLight);
	cubeList.push_back(pencilEraser);

	//Pencil 2 Objects
	Pyramid pencil2Top(pencilPosition + glm::vec3(0.5f, 1.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "Pencil Top.png", keyLight, fillLight);
	pyramidList.push_back(pencil2Top);
	Cube pencil2Body(pencilPosition + glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.2f, 2.0f, 0.2f), "Pencil Body.png", keyLight, fillLight);
	cubeList.push_back(pencil2Body);
	Cube pencil2Eraser(pencilPosition + glm::vec3(0.5f, -1.1f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "Eraser.png", keyLight, fillLight);
	cubeList.push_back(pencil2Eraser);

	//Cup Pencils are held in
	Cube pencilCup(pencilCupPosition, glm::vec3(1.0f, 1.5f, 1.0f), "Cup.png", keyLight, fillLight);
	cubeList.push_back(pencilCup);

	//Computer Objects
	Cube computerBase(computerPosition + glm::vec3(0.0f, -1.4f, -10.0f), glm::vec3(5.0f, 1.0f, 3.0f), "Computer Base.png", keyLight, fillLight);
	cubeList.push_back(computerBase);
	Cube computerStand(computerPosition + glm::vec3(0.0f, -1.4f, -10.0f), glm::vec3(1.0f, 3.0f, 1.0f), "Computer Base.png", keyLight, fillLight);
	cubeList.push_back(computerStand);
	Cube computerBody(computerPosition + glm::vec3(0.0f, 4.0f, -10.0f), glm::vec3(16.0f, 9.0f, 1.0f), "Computer Base.png", keyLight, fillLight);
	cubeList.push_back(computerBody);
	Cube computerScreen(computerPosition + glm::vec3(0.0f, 4.0f, -9.5f), glm::vec3(15.0f, 8.0f, 0.1f), "Computer Screen.png", keyLight, fillLight);
	cubeList.push_back(computerScreen);

	//Keyboard Object
	Cube keyBoard(computerPosition + glm::vec3(0.0f, -1.0f, -3.0f), glm::vec3(8.0f, 0.3f, 4.0f), "Computer Screen.png", keyLight, fillLight);
	cubeList.push_back(keyBoard);

	//Book stack Object
	Cube Book1(bookStackPosition + glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 0.5f, 5.0f), "Book1.png", keyLight, fillLight);
	cubeList.push_back(Book1);
	Cube Book2(bookStackPosition + glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(2.5f, 0.5f, 5.5f), "Book2.png", keyLight, fillLight);
	cubeList.push_back(Book2);
	Cube Book3(bookStackPosition + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(2.75f, 0.5f, 4.0f), "Book3.png", keyLight, fillLight);
	cubeList.push_back(Book3);
	Cube Book4(bookStackPosition + glm::vec3(0.0f, 1.5f, 0.0f), glm::vec3(2.0f, 0.5f, 4.0f), "Book4.png", keyLight, fillLight);
	cubeList.push_back(Book4);

	//Linking and uniform assignment of lights
	keyLight.LinkAttrib();
	keyLight.AssignUniforms();
	fillLight.LinkAttrib();
	fillLight.AssignUniforms();

	//Linking and uniform assignment of table
	table.LinkAttrib();
	table.AssignUniforms();

	//Linking and uniform assignment of Cubes
	for (Cube c : cubeList)
	{
		c.LinkAttrib();
		c.AssignUniforms();
	}

	//Linking and uniform assignment of Pyramids
	for (Pyramid p : pyramidList)
	{
		p.LinkAttrib();
		p.AssignUniforms();
	}

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//Lights buildings
		keyLight.Build(camera);
		fillLight.Build(camera);

		//Iterates through all the cubes to build them in scene
		for (Cube c : cubeList)
		{
			c.Build(camera);
		}

		//Iterates through all the pyramids to build them in the scene
		for (Pyramid p : pyramidList)
		{
			p.Build(camera);
		}

		//building table
		table.Build(camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	pencilTop.Delete();
	pencilBody.Delete();
	pencilEraser.Delete();
	table.Delete();
	keyLight.Delete();
	fillLight.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}




