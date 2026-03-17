#include "../SpriteRenderer2D.hpp"
#include "../RendererShared.hpp"

#include <extern/glm/gtc/type_ptr.hpp>

using namespace engine;
using Shared = internal::RendererShared;

void SpriteRenderer2D::draw() {

	auto& state = internal::EngineState::getState<SpriteRenderer2DState>(id);

	glBindVertexArray(state.VAO);
	glUseProgram(state.shaderProgram);

	auto& shared = internal::EngineState::getShared<Shared>();

	int width, height;
	glfwGetFramebufferSize(shared.window, &width, &height);
	float aspect = (float)width / (float)height;
	glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

	glUniformMatrix4fv(glGetUniformLocation(state.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, 3);

}