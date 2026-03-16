#include "../RendererShared.hpp"

using namespace engine::internal;

void RendererShared::preFrame() {

  glfwMakeContextCurrent(window);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void RendererShared::postFrame() {

  glfwSwapBuffers(window);
  glfwPollEvents();
  
}
