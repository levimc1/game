#include "../../context.hpp"

 using namespace engine;

L::Result Context::running() {
  
  if (!glfwWindowShouldClose(this->state.renderer.window)) {
    return L::Result::SUCCESS;
  }

  return L::Result::STOP;
}
