#pragma once

#include "engine/systems/ChunkRendererState.hpp"
#include <cstdint>
#include <engine/state.hpp>

namespace engine {

  struct ChunkRendererSchema {

  };

  struct ChunkRenderer {
    
    ChunkRendererSchema schema;
    
    // Conceptnek
    size_t id;

    private:
    inline internal::ChunkRendererState& getState() {
      return std::get<internal::ChunkRendererState>(internal::EngineState::getState(id));
    }

    public:
    


    // funkciók

  };

}
