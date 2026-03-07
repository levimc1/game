#include "engine/states/renderer/state.hpp"
#include <engine/context.hpp>

using namespace engine;

L::Result Context::draw() {
  
  internal::RendererState& renderer = this->state.boundRenderer();
  
  glUseProgram(renderer.shader);

  glBindVertexArray(renderer.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  return L::Result::SUCCESS;
}
