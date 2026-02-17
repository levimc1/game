#include <stdio.h>
#include <GLFW/glfw3.h>

int main() {	
	printf("Hello, world");

  if (!glfwInit()) { 
    // sikertelen betltés
  }  
  

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  GLFWwindow* window = glfwCreateWindow(300, 300, "Ablak", NULL, NULL);
  
  if (!window) {
    // sikertelen ablak létrehozás
  }

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {

  }
  
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}



