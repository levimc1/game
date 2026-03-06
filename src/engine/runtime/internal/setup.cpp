#include "../../context.hpp"

using namespace engine;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  
  glViewport(0, 0, width, height);
}

L::Result Context::setup() {
  
  // Semmi beállítás nincsen. csak egy kocka rajzoló.
  
  glfwInit();

  GLFWwindow*& window = this->state.renderer.window;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->state.renderer.window = glfwCreateWindow(800, 600, "Windows 67", NULL, NULL);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  return L::Result::SUCCESS;
}
