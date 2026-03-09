#include "../../context.hpp"

using namespace engine;

L::Result Context::cleanup() {
  
  glfwTerminate();

  return L::Result::SUCCESS;
}
