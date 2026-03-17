#include "../Renderer.hpp"


void Renderer::preDraw() {

  glfwMakeContextCurrent(window);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

}

void Renderer::postDraw() {

  glfwSwapBuffers(window);
  glfwPollEvents();
  
}
