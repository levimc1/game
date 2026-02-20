
// -- Normál includeok
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>


// -- OpenGL specifikus includeok
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Macro mert nem találom a backslash-t a billentyűzetemen
const char NLINE[2] = "\n";

// - Segítő a -- Viewport hoz
void framebuffer_resize(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// - Segítő a rajzoláshoz
// TODO: változókat Renderer specifikus headerbe amikor ott jársz!
// Háromszög szögei
// -1,-1   * - - - *   1,-1
//       | - - - |
//       | -0,0- |
// -1,1   * - - - *   1,1
float vertices[] = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f,
   0.5f,  0.5f, 0.0f
};
// 
unsigned int indices[] = {
  0,1,2 , 1,2,3
};
// Kocka - source: https://pastebin.com/XiCprv6S
    GLfloat cvertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7
 
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15
 
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
        0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
    };
    GLuint cindices[] = {
        // front and back
        0, 3, 2,
        2, 1, 0,
        4, 5, 6,
        6, 7 ,4,
        // left and right
        11, 8, 9,
        9, 10, 11,
        12, 13, 14,
        14, 15, 12,
        // bottom and top
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };
// VertexBufferObject
unsigned int VBO; 
unsigned int VAO;
unsigned int IBO;

// - Segítő az OpenGL-hez
// Shaderek
std::string read_shader(const std::string& file_path) {

  std::ifstream file(file_path);

  if (!file.is_open()) { 
    std::cout << "Nem sikerült megnyitni a shader filet:"
    << file_path << std::endl;
  }

  std::stringstream buff;
  buff << file.rdbuf();

  return buff.str();
}

// compile is
GLuint compile_shader(GLenum type, const std::string& src) {
  
  GLuint shader = glCreateShader(type);
  
  const GLchar* s = src.c_str();

  glShaderSource(shader, 1, &s, nullptr);

  glCompileShader(shader);
  
  // type név
  std::string typestr = (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";

  // Hibák
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[512];
    glGetShaderInfoLog(shader, 512, nullptr, info);

    std::cout << typestr << "Shader compile hiba: " << NLINE << info << std::endl;  
  }

  return shader;
}
// Alap shaderek betöltése
GLuint load_shaders() { // -> Program
  std::string vert = read_shader("shader.vert");
  std::string frag = read_shader("shader.frag");
  
  GLuint v_shader = compile_shader(GL_VERTEX_SHADER, vert);
  GLuint f_shader = compile_shader(GL_FRAGMENT_SHADER, frag);
  
  GLuint shader = glCreateProgram();
  glAttachShader(shader, v_shader);
  glAttachShader(shader, f_shader);
  glLinkProgram(shader);
  
  glDeleteShader(v_shader);
  glDeleteShader(f_shader);

  return shader;
}


int main() {
  
  std::cout << "Hello, world!" << std::endl;
  std::cout << std::filesystem::current_path() << std::endl;
  std::filesystem::current_path(std::filesystem::current_path() / "src");

  // --- Init
  // -- GLFW alapok beállítása
  glfwInit(); // Általában jó
  // Verzió, stb beállításal
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // -- Ablak létrehozása
  GLFWwindow* window; // -- NEM LOCAL VAR --
  window = glfwCreateWindow(800, 600, "Ablak", NULL, NULL);
  if ( window == NULL ) {
    std::cout << "Nem sikerült a GLFW ablakot lérehozni!" << std::endl;
    glfwTerminate();
    return -1;
  }
  // Ablak beállítása a StateMachine-ben
  glfwMakeContextCurrent(window);

  // -- Glad betöltése OpenGL függvényekhez
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Nem sikerült betölteni a GLAD-ot!" << std::endl;     
  }
  
  // --- Kisebb ablak beállítások
  // -- Viewport
  glViewport(0, 0, 800, 600); // Hülyeség mert WM-em van
  glfwSetFramebufferSizeCallback(window, framebuffer_resize); // de ez megoldja
  
  // --- OpenGL dolgok beállítása
  // -- Bufferek
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &IBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Lehetséges több buffer kell
                                      // Akkor ezt töröld és vidd Loop-ba
  glBufferData(GL_ARRAY_BUFFER, sizeof(cvertices), cvertices, GL_STATIC_DRAW); // Adat megadása
  // IBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cindices), cindices, GL_STATIC_DRAW); 
  // VAO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // -- Shaderek
  GLuint shader = load_shaders();
  
  // előre hozva Input modifikéció miatt
  glm::vec3 camera = glm::vec3(0.0f, 0.0f, -5.0f);
  float cam_speed = 1.0f / 60;
  glm::vec3 camera_front = glm::vec3(0.5f, 0.0f, 1.0f); // Z irányba
  glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
  // --- Loop
  while (!glfwWindowShouldClose(window)) {
    // Runtime cucclik
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      camera += camera_front * cam_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      camera -= camera_front * cam_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      camera += glm::normalize(glm::cross(camera_front, cam_up)) * cam_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      camera -= glm::normalize(glm::cross(camera_front, cam_up)) * cam_speed;
    }
    // Rajzolás
    glUseProgram(shader);
    
    // Uniformok
    glm::mat4 model = glm::mat4(1.0f);
    // Eltolás, stb, ez normálisna hagyja
    glm::mat4 view = glm::lookAt(
      camera,
      camera + camera_front,
      cam_up
    );
    // Camera pozíció, közép, fel iránya.
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glm::mat4 projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(width) / static_cast<float>(height),
      0.1f,
      100.0f
    );
    int model_loc = glGetUniformLocation(shader, "model");
    int view_loc = glGetUniformLocation(shader, "view");
    int proj_loc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Ablak törlése Türkiz színnel     
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

    // Hogy ne legyen "Nem válaszol"
    glfwSwapBuffers(window);
    glfwPollEvents(); // Gombnyomások itt
  }

  // --- Cleanup
  glfwTerminate();

  return 0;
}
