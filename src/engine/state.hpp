#pragma once

// Circular dependecy elkerülésére. 

#include <cstddef>
#include <optional>
#include <variant>
#include <vector>
#include <functional>

#include "systems/TestRendererState.hpp"
#include "systems/RendererShared.hpp"
#include "systems/ChunkRendererState.hpp"

// Összes state típus 
using State = std::variant<std::monostate, 
      engine::internal::TestRendererState, 
      engine::internal::ChunkRendererState>;

namespace engine::internal {

  struct EngineState {

    inline static std::vector<State> states;
    
    inline static State& getState(size_t index) {return states[index];}
  };
  
  struct EngineSharedState {
    
    inline static std::vector<std::function<void()>> setupHooks;
    inline static std::vector<std::function<void()>> beginFrameHooks;
    inline static std::vector<std::function<void()>> endFrameHooks;
    inline static std::vector<std::function<void()>> cleanupHooks;

    inline static RendererShared* renderer = NULL;
    inline static void useRenderer() {
      if (renderer == NULL) {
        renderer = new RendererShared{};
        // Hookok regisztrálása
        setupHooks.push_back(       [](){renderer->setup();       }); 
        beginFrameHooks.push_back(  [](){renderer->beginFrame();  }); 
        endFrameHooks.push_back(    [](){renderer->endFrame();    }); 
        cleanupHooks.push_back(     [](){renderer->cleanup();     }); 
      }
    }
    inline static RendererShared& getRenderer() {
      return *renderer;      
    };

  };

}


