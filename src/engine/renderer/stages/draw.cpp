#include "../renderer.hpp"

#if defined(M_RENDERER)
#include <engine/context.hpp>

#include <print>

int draw() {  
    
  renderer::Module* mod = renderer::get();

  if (glfwWindowShouldClose(mod->ctx.window) { engine::should_shutdown = true }
  else {
    
    glfwSwapBuffers(mod->ctx.window);
    glfwPollEvents();

  } 

  return 0;
}
#endif;
