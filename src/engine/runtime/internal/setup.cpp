#include "../../context.hpp"

#include <engine/runtime/utils/utils.hpp>
#include <engine/states/renderer/global.hpp>

// TODO: -> oszd fel a kódot shcemakra

using namespace engine;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  
  glViewport(0, 0, width, height);
}

L::Result Context::setup() {
  
  // Semmi beállítás nincsen. csak egy kocka rajzoló.
   
  // Csak egyszer
  if (!this->state.renderers.empty()) {
    glfwInit();
  

    GLFWwindow*& window = this->state.renderer.window;
  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->state.renderer.window = glfwCreateWindow(800, 600, "Windows 67", NULL, NULL);
  
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
      GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
      {
        if (severity == GL_DEBUG_SEVERITY_HIGH) {
            std::println("[GL ERROR] {}", message);
        }
      }, nullptr);

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  }
  
  for (auto& renderer : this->state.renderers) {
    // NEM GLOBÁLIS STATE-BŐL! SETUP NEM TUDHAT BINDOKRÓL.
    GLuint& VAO    = renderer.VAO;
    GLuint& VBO    = renderer.VBO;
    GLuint& EBO    = renderer.EBO;
    GLuint& shader = renderer.shader;
    shader = utils::loadShader("shader.vert", "shader.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(renderer::vertices), renderer::vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderer::indices), renderer::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                // -ás sloton
        3,                // darab 
        GL_FLOAT,         // 
        GL_FALSE,         // ami nincs normalizálva
        3 * sizeof(float),// mekkora?
        (void*)0);        // és itt kezdődik
    glad_glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
    
  return L::Result::SUCCESS;
}
