#include "../context.hpp"

using namespace engine;

int Context::run(const RunSchema& schema) {
  
  setup();

  while ( running() == L::Result::SUCCESS ) {

    if (schema.frame) {
      glClearColor(0.0f, 1.0f, 0.4f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      schema.frame();
    }

    // Ha van ablak
    // Past Frame
    glfwSwapBuffers(this->state.renderer.window);
    glfwPollEvents();

  }

  cleanup();

  return 0;
}
