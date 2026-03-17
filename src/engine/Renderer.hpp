 #pragma once

#include <engine/registry.hpp>
// Csak dísz

#include <string>

#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>


struct Renderer {
  
  GLFWwindow* window; 

  void setup();
  void preDraw();
  void postDraw();
  void cleanup();
  
  static GLuint loadShader(const std::string& verRelPath, const std::string& fragRelPath);
  
  // Amúgy QuadVertex-re abszolút semmi szükség. 
  // Ha sok lesz vidd át RendererMath-ba vagy vmi.

  struct QuadVertex {
    glm::vec3 pos;
  };

  struct QuadVertexUV {
    glm::vec3 pos;
    glm::vec2 uv;
  };

  static inline QuadVertex q_vertices[] = {
    { {-0.5f, -0.5f, 0.0f} },
    { { 0.5f, -0.5f, 0.0f} },
    { { 0.5f,  0.5f, 0.0f} },
    { {-0.5f,  0.5f, 0.0f} },
  };

  static inline QuadVertexUV q_vertices_uv[] = {
    { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f} },
    { { 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f} },
    { { 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f} },
    { {-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f} },
  };

  static inline unsigned int q_indices[] = {
    0, 1, 2,
    2, 3, 0,
  };
};
