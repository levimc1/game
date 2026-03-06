#pragma once

#include "states/renderer/state.hpp"
#include <cstddef>
#include <vector>

namespace engine {

  struct State {
  // A teljes state, több state-ből
    
    internal::RendererStateGlobal renderer;
    std::vector<internal::RendererState> renderers;
    std::vector<size_t> rendererBindStack; 
    // std::stack adapter így semmi értelme.
    internal::RendererState& boundRenderer();

  };

}
