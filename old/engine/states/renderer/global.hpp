#pragma once 

namespace engine::renderer {
   
  inline float vertices[] = {
    -0.5f,  0.5f, 0.0f,  // bal felső
     0.5f,  0.5f, 0.0f,  // jobb felső
     0.5f, -0.5f, 0.0f,  // jobb alsó
    -0.5f, -0.5f, 0.0f   // bal alsó
  };

  inline unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

}

