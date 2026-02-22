
#include "../renderer.hpp"

#if defined(M_RENDERER)
//#include <iostream>
#include <print>

// újraméretezés
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  
  std::println("Ablak újraméretzve: {}x{}", width, height);
  glViewport(0, 0, width, height);
}


int init() {
    
  std::println("Renderer betöltése.");
  renderer::Module* mod = renderer::get();

  if (!glfwInit()) {
    std::println("Nem sikerült GLFW-t betölteni!"); 
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  mod->ctx.window = glfwCreateWindow(640, 480, "Ablak", NULL, NULL);
  if (!mod->ctx.window) {
    std::println("Nem sikerült létrehozni az ablakot!");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(mod->ctx.window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) {
    std::println("Nem sikerült GLAD-ot betölteni!");
    glfwTerminate;
    return -1;
  }
  
  glfwSetFrameBufferSizeCallback(window, framebuffer_size_callback);

  // ide buffer és stb!
 

  return 0; 
}

#endif
