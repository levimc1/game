#include "../TestRenderer.hpp"
#include <GLFW/glfw3.h>

void engine::TestRenderer::draw() {
 
  auto& state = internal::EngineState::getState<internal::TestRendererState>(id);

  glBindVertexArray(state.VAO);
  glUseProgram(state.shaderProgram);
 
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  
}
