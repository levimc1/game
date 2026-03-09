#pragma once

#include "states/renderer/state.hpp"
#include <cstddef>
#include <print>
#include <vector>
#include <stdexcept>

// TODO: error handling-re tudod a e.printErrors! 

namespace engine {

  struct State {
  // A teljes state, több state-ből
    
    internal::RendererStateGlobal renderer;
    std::vector<internal::RendererState> renderers;
    std::vector<size_t> rendererBindStack; 
    // std::stack adapter így semmi értelme.
    inline internal::RendererState& boundRenderer() {
      if (rendererBindStack.empty()) {
        throw std::runtime_error("[Context] Nincs bound renderer");
      }
      size_t id = rendererBindStack.back();
      if (id >= renderers.size()) {
        throw std::runtime_error("[Context] Érvénytelen renderer handle - ");
      }
      return renderers.at(id);
    }

  };

}
