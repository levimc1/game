#include "../RendererShared.hpp"

using namespace engine::internal;

void RendererShared::preFrame() {

  glfwMakeContextCurrent(window);

}

void RendererShared::postFrame() {

  glfwSwapBuffers(window);
  glfwPollEvents();
  
}
