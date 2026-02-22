
#include <game.hpp>

#if defined(M_RENDERER)

#include "../renderer.hpp"
#include <iostream>

namespace renderer {

  int init() {
    
    std::cout << "Renderer init" << std::endl; 
    
    Module* mod = get();

    return 0; 
  }

}
#endif
