#include "../TestRenderer.hpp"
#include "engine/state.hpp"
#include "engine/systems/RendererShared.hpp"
#include "engine/systems/TestRendererState.hpp"

#include <GLFW/glfw3.h>
#include <cstddef>

using namespace engine;

using Shared = internal::RendererShared;

void TestRenderer::setup() {
  
  auto& state = internal::EngineState::getState<internal::TestRendererState>(id);
  
  // Bufferek és stb
  
  state.shaderProgram = Shared::loadShader("shader.vert", "shader.frag");

  glGenVertexArrays(1, &state.VAO);
  glGenBuffers(1, &state.VBO);
  glGenBuffers(1, &state.EBO);
    
  glBindVertexArray(state.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Shared::q_vertices), Shared::q_vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Shared::q_indices), Shared::q_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(
      0,                  // A atrribute száma
      3,                  // Komponensek száma
      GL_FLOAT,           // Komponensek típusa
      GL_FALSE,           // Normalizáció
      sizeof(Shared::QuadVertex),         // Stride mérete        (teljes méret) 
      (void*)offsetof(Shared::QuadVertex, pos)   // Offset az előzőtől   (Offset a teljes méretben)
  );
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}
