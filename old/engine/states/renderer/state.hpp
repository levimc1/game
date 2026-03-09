#pragma once

#include <engine/common.hpp>
#include "schema.hpp"
// OpenGL
#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>

namespace engine::internal {
  
  struct RendererStateGlobal {
  // Globális, setup hozza létre ha van egy renderer, 
  // majd azok használják
    
    GLFWwindow* window;

  };
  
  struct RendererState {
  // Bindolt, rendszerenkénti
       
    engine::RendererSchema schema; 
    GLuint VAO, VBO, EBO, shader;
  };

}
