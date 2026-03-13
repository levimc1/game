#pragma once

#include "engine/systems/TestRendererState.hpp"
#include <cstddef>
#include <engine/state.hpp>

namespace engine {
  
  struct TestRendererSchema {

  };

  struct TestRenderer {
    
    TestRendererSchema schema;
    // És konnekció
    
    // COnceptnek
    size_t id;

    private:
    inline internal::TestRendererState& getState() {
      return std::get<internal::TestRendererState>(internal::EngineState::getState(id));
    }

    public:
        
    void setup(std::vector<State>& state);
    inline void cleanup() {};
    inline void useShareds() {internal::EngineSharedState::useRenderer();};

    // Funkció
    void draw();
    inline bool condition() {
      auto& state = getState();
      return !glfwWindowShouldClose(internal::EngineSharedState::getRenderer().window);
    }
    
  };  

}
