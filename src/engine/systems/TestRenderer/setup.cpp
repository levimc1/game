#include "../TestRenderer.hpp"
#include "engine/systems/TestRendererState.hpp"

#include <GLFW/glfw3.h>
#include <cstddef>
#include "data.hpp"

using namespace engine;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void TestRenderer::setup(std::vector<State>& s) {

  s[id] = internal::TestRendererState{};
  auto& state = getState();
  
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  state.window = glfwCreateWindow(800, 600, "Windows 13", NULL, NULL);
  glfwMakeContextCurrent(state.window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(state.window, framebufferSizeCallback);

  // Bufferek és stb
  
  state.shaderProgram = testrenderer::loadShader("shader.vert", "shader.frag");

  glGenVertexArrays(1, &state.VAO);
  glGenBuffers(1, &state.VBO);
  glGenBuffers(1, &state.EBO);
    
  glBindVertexArray(state.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(testrenderer::vertices), testrenderer::vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testrenderer::indices), testrenderer::indices, GL_STATIC_DRAW);

  glVertexAttribPointer(
      0,                  // A atrribute száma
      3,                  // Komponensek száma
      GL_FLOAT,           // Komponensek típusa
      GL_FALSE,           // Normalizáció
      3 * sizeof(float),  // Stride mérete        (teljes méret) 
      (void*)0            // Offset az előzőtől   (Offset a teljes méretben)
  );
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}
