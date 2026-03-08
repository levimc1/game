#include "../../context.hpp"
#include "engine/common.hpp"
#include "engine/states/renderer/state.hpp"

#include <engine/runtime/utils/utils.hpp>
#include <engine/states/renderer/global.hpp>
#include <print>

// TODO: -> oszd fel a kódot shcemakra

// debug eszköz
#define HERE std::println("{}:{}", __FILE__, __LINE__);

using namespace engine;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  
  glViewport(0, 0, width, height);
}

L::Result Context::setup() {  
  // Semmi beállítás nincsen. csak egy kocka rajzoló.

  // Csak egyszer
  if (!this->state.renderers.empty()) {

    if (!glfwInit()) {
      std::println("[SETUP] Nem sikerült betölteni a glfw-t");
      return L::Result::FAILURE;
    }

    GLFWwindow*& window = this->state.renderer.window;
  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    this->state.renderer.window = glfwCreateWindow(800, 600, "Windows 67", NULL, NULL);
    if (!window) {
      std::println("[SETUP] Nem sikerült lérehozni az abalakot!");
      return L::Result::FAILURE;
    }
  
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::println("[SETUP] Nem sikerült betölteni a GLAD-ot!");
      return L::Result::FAILURE;
    }

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
