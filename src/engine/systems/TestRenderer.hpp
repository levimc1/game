#pragma once

#include <cstddef>
#include <engine/state.hpp>

namespace engine {
  
  struct TestRendererSchema {

  };

  struct TestRenderer {
    
    internal::TestRendererState& state;

    TestRendererSchema schema;
    // És konnekció
    
    // COnceptnek
    size_t id;
        
    void setup(State& state);
    void cleanup();

    // Funkció
    void draw();
    inline bool condition() {
      return !glfwWindowShouldClose(state.window);
    }
    
  };  

}
