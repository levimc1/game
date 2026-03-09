#include "../TestRenderer.hpp"
#include "engine/systems/TestRendererState.hpp"

#include <GLFW/glfw3.h>
#include <cstddef>

using namespace engine;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void TestRenderer::setup(State& s) {

  s = internal::TestRendererState{};
  state = std::get<internal::TestRendererState>(s);
  
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

  glGenVertexArrays(1, &state.VAO);

  glGenBuffers(1, &state.VBO);
  glGenBuffers(1, &state.EBO);

  glBindVertexArray(state.VAO);


}
