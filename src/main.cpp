#include <iostream>

//#define M_RENDERER
//#include <engine/renderer/stages.hpp>

// Macrok itt
#define CALL(x) { int _tmp = x; stage++; std::cout << "Hívás: " << stage << " - " << #x << std::endl; if (_tmp !=0) {std::cout << "Hiba híváskor" << std::endl; return _tmp;};}
// azért ilyen rondán 1 sorba mert nem találom a backslash karaktert


int main() {

  std::cout << "Hello, world!" << std::endl;
  int stage = 0;

  // --- Stage 0 - Module setup
  CALL(renderer::init());


  // --- Stage 1 - Init
  

  
  // --- Stage 2 - Loop
  


  // --- Stage 3 - Cleanup
  

  return 0;
}
