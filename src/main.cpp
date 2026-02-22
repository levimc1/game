#include <print>

// OpenGL include-ok
#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  std::println("Framebuffer újramérezve: {}x{}", width, height);
}

int main() {
  
  std::println("Hello, {}", "World!");
  
  // Setup
  
  if (!glfwInit()) {
    std::println("Nem sikerült betölteni GLFW-t!");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLOBÁLIS VÁLTOZÓ ITT!
  GLFWwindow* window = glfwCreateWindow(800, 600, "Ablak", NULL, NULL);
  if (!window) {
    std::println("Nem sikerült az ablakot létrehozni!");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::println("Nem sikerült betölteni a GLAD-ot!");
    glfwTerminate();
    return -1;
  }

  // utiltí szerű dolgo
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // Loop

  while (!glfwWindowShouldClose(window)) { 
    
    // Pre-tick

    glfwSwapBuffers(window);
    glfwPollEvents();
    
    // Tick
    

    // Frame

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

  }

  // Cleanup

  glfwTerminate();

  return 0;
}
