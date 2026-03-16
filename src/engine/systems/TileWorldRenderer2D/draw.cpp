#include "../TileWorldRenderer2D.hpp"

using namespace engine;

void TileWorldRenderer2D::draw() {

	auto& state = internal::EngineState::getState<TileWorldRenderer2DState>();

	glBindVertexArray(state.VAO);
	glUseProgram(state.shaderProgram);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, 3);
}