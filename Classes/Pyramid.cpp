#include"Pyramid.h"
#include"Light.h"

Pyramid::Pyramid(glm::vec3 position, glm::vec3 scale, const char* texture, Light keyLight, Light fillLight)
{
	Pyramid::position = position;
	Pyramid::texture = Texture(texture, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Pyramid::keyLight = keyLight;
	Pyramid::fillLight = fillLight;
	Pyramid::shader = Shader("default.vert", "default.frag");

	Pyramid::vao = VAO();
	Pyramid::vbo = VBO(vertices, sizeof(vertices));
	Pyramid::ebo = EBO(indices, sizeof(indices));
	
	model = glm::translate(model, position);
	Pyramid::texture.texUnit(Pyramid::shader, "tex0", 0);
	model = glm::scale(model, scale);
}

Pyramid::Pyramid(glm::vec3 position, glm::vec3 scale, Shader shader, Light keyLight, Light fillLight)
{
	Pyramid::position = position;
	Pyramid::keyLight = keyLight;
	Pyramid::fillLight = fillLight;

	Pyramid::vao = VAO();
	Pyramid::vbo = VBO(vertices, sizeof(vertices));
	Pyramid::ebo = EBO(indices, sizeof(indices));

	model = glm::translate(model, position);
	model = glm::scale(model, scale);
}

// rotates the object in degrees over a vector
void Pyramid::Rotate(float amount, glm::vec3 vector)
{
	model = glm::rotate(amount / 57.2957795131f, vector);
}

// links vertex, vertex color, texture cord, and normal attributes to the vao.
void Pyramid::LinkAttrib()
{
	vao.Bind();

	// Links VBO attributes such as coordinates and colors to VAO
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vao.Unbind();
	vbo.Unbind();
}

// assignes the model, key light and fill light positions and color to the appropiate uniforms
void Pyramid::AssignUniforms()
{
	// Pyramid shader is activated to assign the key light and the filler light's position and color to do the math for the lighting.
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	// Key light attributes (color and position) are passed into the shader
	glUniform4f(glGetUniformLocation(shader.ID, "keyLightColor"), keyLight.color.x, keyLight.color.y, keyLight.color.z, keyLight.color.w);
	glUniform3f(glGetUniformLocation(shader.ID, "keyLightPos"), keyLight.position.x, keyLight.position.y, keyLight.position.z);
	// Filler light attributes (color and position) are passed into the shader
	glUniform4f(glGetUniformLocation(shader.ID, "fillLightColor"), fillLight.color.x, fillLight.color.y, fillLight.color.z, fillLight.color.w);
	glUniform3f(glGetUniformLocation(shader.ID, "fillLightPos"), fillLight.position.x, fillLight.position.y, fillLight.position.z);
}

// draws the object in line with the camera 
void Pyramid::Build(Camera camera)
{
	// Tells OpenGL we want to use our shader
	shader.Activate();
	// Exports the camera Position to the Fragment Shader for specular lighting
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Export the camMatrix to the Vertex Shader of the shape
	camera.Matrix(shader, "camMatrix");
	// Binds texture so that is appears in rendering
	texture.Bind();
	// Bind the VAO so OpenGL knows to use it
	vao.Bind();
	ebo.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

// deletes all the created parts
void Pyramid::Delete()
{
	shader.Delete();
	texture.Delete();
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
}