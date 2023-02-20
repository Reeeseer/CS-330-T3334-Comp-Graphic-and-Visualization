#include"Light.h"

Light::Light(glm::vec3 position, glm::vec4 color)
{
	Light::shader = shader;
	Light::position = position;
	Light::color = color;
	Light::model = glm::mat4(1.0f);

	Light::vao = VAO();
	Light::vbo = VBO(vertices, sizeof(vertices));
	Light::ebo = EBO(indices, sizeof(indices));
	model = glm::translate(model, position);
}


void Light::LinkAttrib()
{
	vao.Bind();

	// Links VBO attributes such as coordinates and colors to VAO
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	vao.Unbind();
	vbo.Unbind();
}

void Light::AssignUniforms()
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), color.x, color.y, color.z, color.w);
}

void Light::Build(Camera camera)
{
	// Tells OpenGL we want to use our shader
	shader.Activate();
	// Exports the camera Position to the Fragment Shader for specular lighting
	camera.Matrix(shader, "camMatrix");
	// Bind the VAO so OpenGL knows to use it
	vao.Bind();
	ebo.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Light::Delete()
{
	shader.Delete();
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
}