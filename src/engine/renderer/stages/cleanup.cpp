#include "../renderer.hpp"

#if defined(M_RENDERER)

int renderer::cleanup() {
  
  glfwTerminate();
  return 0;
}

#endif
