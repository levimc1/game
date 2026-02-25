#include <filesystem>
#include <fstream>
#include <print>
#include <string>

// OpenGL include-ok
#include <extern/glad/glad.h>
#include <GLFW/glfw3.h>
#include <extern/glm/glm.hpp>

// én megpróbáltam
const char newline[2] =  "\n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  std::println("Framebuffer újramérezve: {}x{}", width, height);
}

void process_input(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

// Undorító, egyszeres shader betöltő függvény
// FONTOS! LOKÁLIS assets/shader-re!
GLuint create_program(const std::string& vert_path, const std::string& frag_path) {
  
  // Lusta vagyok több függvényt létrehozni. Így minden egyben.
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  
  // build mappától!
  std::filesystem::path base_path ="src/assets/shaders";
std::println("Shader path: {}", std::filesystem::absolute(base_path).string());
  std::ifstream vert_file(base_path / vert_path);
  std::ifstream frag_file(base_path / frag_path);
  
  if (!vert_file.is_open()) {std::println("Nem sikerült megnyitni a vertex shader file-t! {}", vert_path);}
  if (!frag_file.is_open()) {std::println("Nem sikerült megnyitni a fragment shader file-t! {}", frag_path);}
  
  std::string vert_src;
  std::string frag_src;

  // Ez nem hiszem hogy a legjobb módszer erre.
  std::string line;
  while (std::getline(vert_file, line)) {
    vert_src += line + "\n";
  }
  while (std::getline(frag_file, line)) {
    frag_src += line + "\n";
  }
  const char* src1 = vert_src.c_str();
  glShaderSource(vert_shader, 1, &src1, NULL);
  glCompileShader(vert_shader);
  const char* src2 = frag_src.c_str();
  glShaderSource(frag_shader, 1, &src2, NULL);
  glCompileShader(frag_shader);
  
  int success;
  GLchar info_log[512];
  glad_glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert_shader, 512, NULL, info_log);
    std::println("Hiba vertex shaderben! -> {}", info_log);
  }
  glad_glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
    std::println("Hiba fragment shaderben! -> {}", info_log);
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);
  glLinkProgram(program);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  return program;
} 

int main() {
  
  std::println("Hello, {}", "World!");
  
  // Setup
  
  if (!glfwInit()) {
    std::println("Nem sikerült betölteni GLFW-t!");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLOBÁLIS VÁLTOZÓ ITT!
  GLFWwindow* window = glfwCreateWindow(800, 600, "Ablak", NULL, NULL);
  if (!window) {
    std::println("Nem sikerült az ablakot létrehozni!");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::println("Nem sikerült betölteni a GLAD-ot!");
    glfwTerminate();
    return -1;
  }

  // utilty szerű dolgok
  glViewport(0, 0, 800, 600);
  // Callbackek glfwMakeContextCurrent és GLAD betöltés után ha OpenGL-t érint. azaz ide jó
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // OpenGL beállítása
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  
  /* Gondolj OpenGL-re így!
   *
   * Olyan mint a scratch. Úgy kezdődött hogy csak glBegin -> VONALAK RAJZOLÁSA
   * Majd a nép többet akart, és többet, és többet. 
   * Ezért egyszerű és erős. A közösség formálja.
   * Magáról ahogy írsz benne.
   * Vannak state-olvasó és state-mutáló függvények.
   * A state tartalmaz objecteket (pld VBO, VAO, IBO) - ezért van O a végén!
   * Amik a globális OpenGL stateben vannak eltárolva. 
   * Majd ezek alapján rajzol.
   * A rajzolásról.
   * Az adatod a CPU-n kezdi, majd a bufferek által átkerül a GPU-ra.
   * A GPU-n a pipeline a Vertex attribute-ok alapján (Azaz 3D kordináták, stb)
   * 2D pixeleket csinál, ami a frame-ünk!
   * Ez NAGYON szzemélyre szabható! shaderekkel. stb.
   */
  // OpenGL Bufferek felállítása - SOK GLOBÁL VÁLTOZÓ - bemásolva learnOpenGL-ból
  float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };  
  // Objektum rajzolás lépései
  // 0. Létrehozás
  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // 0.5 VAO-ban "Objekt" információ tárolása 
  glBindVertexArray(VAO); // Egy VAO -> Egy "Objektum" azaz chunk, stb.
                          // Ez sajnos kötelező, de praktikus!

  // 1. VBO létrehozása
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
  /* Az Adat egyszer változik, sokszor használt -> STATIC_DRAW
   * Az Adat egyszer változik, kevésszer használt -> STREAM_DRAW
   * Az adat többször változik, és akármennyiszer használt -> DYNAMIC_DRAW
   * */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // 2. Vertex attrib létrehozása
  // VAO ÉS VERTEXATTRIBPOINTER NEM UGYANAZ!!!!
  glVertexAttribPointer(0,                  // 0-ás helyen
                        3,                  // 3 darab    
                        GL_FLOAT,           // float (xyz)
                        GL_FALSE,           // Ne normalizáld
                        3 * sizeof(float),  // Amik 3 float méretűek
                        (void*)0            // És 0 offset a legelejétől
      );
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Csak azért hogy jobban lehessen mozgatni a kódot.
  glBindVertexArray(0);
  
  // 3. Shader létrehozása és használata
  // Shader betöltése file-ból. Sajnos. Mert így sajnos jobb. 
  // Erre írtam egy külön függvényt. Mert ez az unalmas része :(
  GLuint program = create_program("shader.vert", "shader.frag");

  // 4. Rajzolás - EZ A 4 LÉPÉS MINDEN OBJEKTUMÉRT A KÉPERNYŐN!!!!!
  // Ez csak a draw callra érvényes. a process_input és stb nem objektenként.
  while (!glfwWindowShouldClose(window)) { 
    
    // Pre-tick
    
    process_input(window);
    
    // Tick
    

    // Frame
    
    // frame-ben kell ez. 
    glUseProgram(program);
    glBindVertexArray(VAO); // VAO nem tárol shadert!

    glClear(GL_COLOR_BUFFER_BIT);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 0 offset-el rajzolj 6 indexelt háromszöget.

    // Past-frame
    
    glfwSwapBuffers(window);
    glfwPollEvents();

  }

  // Cleanup
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(program);

  glfwTerminate();

  return 0;
}
