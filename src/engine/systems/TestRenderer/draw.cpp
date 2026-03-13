#include "../TestRenderer.hpp"
#include <GLFW/glfw3.h>

void engine::TestRenderer::draw() {
 
  auto& state = getState();
  

  glBindVertexArray(state.VAO);
  glUseProgram(state.shaderProgram);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  
}
