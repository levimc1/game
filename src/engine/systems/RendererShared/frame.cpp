#include "../RendererShared.hpp"

using namespace engine::internal;

void RendererShared::beginFrame() {

  glfwMakeContextCurrent(window);

}

void RendererShared::endFrame() {

  glfwSwapBuffers(window);
  glfwPollEvents();
  
}
