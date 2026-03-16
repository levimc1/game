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
    GLFWwindow* window;

    // AI mer nincs idegem ezt megírni újra.
    static GLuint loadShader(const std::string& verRelPath, const std::string& fragRelPath);
    inline bool condition() {return !glfwWindowShouldClose(window);}
    
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

    //nagyon internal
    std::string windowTitle = "engine::renderer::windowTitle(name)"; // kezdő ha van
  };
  

}

// Módosítások pld új ablak, stb.
namespace engine::renderer {
  
  // setup előtt.
  inline void windowTitle(const std::string& name) {
    internal::RendererShared& renderer = internal::EngineState::getShared<internal::RendererShared>();
    if (!renderer.window) {renderer.windowTitle = name;} else {
      glfwSetWindowTitle(renderer.window, name.c_str());
    }
  }

  inline std::string getWindowTitle() {
    internal::RendererShared& renderer = internal::EngineState::getShared<internal::RendererShared>();
    if (!renderer.window) {return renderer.windowTitle;} else {
      return glfwGetWindowTitle(renderer.window);
    }
  }

}
