#pragma once

#include "../TestRendererState.hpp"
#include <string>

namespace engine::testrenderer {

  inline float vertices[] = {
    -0.5f, -0.5f, 0.0f, // Alsó bal
     0.5f, -0.5f, 0.0f, // Alsó jobb
     0.5f,  0.5f, 0.0f, // Felső jobb
    -0.5f,  0.5f, 0.0f, // Felső bal
  };

  inline unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,
  };
  
  // AI mer nincs idegem ezt megírni újra.
  GLuint loadShader(const std::string& verRelPath, const std::string& fragRelPath);

}
