#pragma once

#include <string>

//OPenGL include-ok talán
#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>

namespace engine::internal {

  struct RendererShared {
    
    // Hookok
    void setup();
    void beginFrame();
    void endFrame();
    void cleanup();

    // Közös state változók
    inline static GLFWwindow* window;

    // AI mer nincs idegem ezt megírni újra.
    static GLuint loadShader(const std::string& verRelPath, const std::string& fragRelPath);

    static inline float vertices[] = {
      -0.5f, -0.5f, 0.0f, // Alsó bal
       0.5f, -0.5f, 0.0f, // Alsó jobb
       0.5f,  0.5f, 0.0f, // Felső jobb
      -0.5f,  0.5f, 0.0f, // Felső bal
    };

    static inline unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0,
    };
  };

}
