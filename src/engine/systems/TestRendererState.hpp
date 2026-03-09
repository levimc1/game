#pragma once

//OPenGL include-ok talán
#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>

namespace engine::internal {

  struct TestRendererState {
    GLFWwindow* window;
    unsigned int VAO, VBO, EBO, shaderProgram;
  };

}
