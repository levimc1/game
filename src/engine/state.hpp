#pragma once

// Circular dependecy elkerülésére. 

#include <variant>
#include <vector>

#include "systems/TestRendererState.hpp"

// Összes state típus 
using State = std::variant<std::monostate, engine::internal::TestRendererState>;

namespace engine::internal {

  struct EngineState {

    inline static std::vector<State> states;
    
    inline static State& getState(size_t index) {return states[index];}
  };

}
