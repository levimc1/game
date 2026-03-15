#pragma once

#include "engine/state.hpp"
#include <string>

//OPenGL include-ok talán
#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>

namespace engine::internal {

  struct RendererShared : public Shared {
    
    RendererShared() : Shared(SystemDesc("RendererShared", SystemDesc::Setup | SystemDesc::Cleanup | SystemDesc::PreFrame | SystemDesc::PostFrame)) {} 

    // Hookok
    void setup() override;
    void preFrame() override;
    void postFrame() override;
    void cleanup() override;

    // Közös state változók
    inline static GLFWwindow* window;

    // AI mer nincs idegem ezt megírni újra.
    static GLuint loadShader(const std::string& verRelPath, const std::string& fragRelPath);
    inline bool condition() {return !glfwWindowShouldClose(window);}

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
