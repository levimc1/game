#include "../SpriteRenderer2D.hpp"
#include "engine/Renderer.hpp"

#include <extern/glm/gtc/type_ptr.hpp>

void SpriteRenderer2D::draw() {

	auto& shared = instance<Renderer>();

	glBindVertexArray(VAO);
	glUseProgram(shaderProgram);

	int width, height;
	glfwGetFramebufferSize(shared.window, &width, &height);
	float aspect = (float)width / (float)height;
	glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, 3);

}
