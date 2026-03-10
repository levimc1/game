#pragma once

#include "state.hpp"
#include <concepts>
#include <cstdint>
#include <functional>
#include <vector>

namespace engine {

  template<typename T>
  concept System = requires(T t, std::vector<State>& s) {
    { t.id } -> std::same_as<size_t&>;
    t.setup(s);
    t.cleanup();
  };

  struct Context {
    
    private:
    inline static internal::EngineState state;
    inline static std::vector<std::function<void()>> stateCleaners;
    // csak cleanup, frame 0%-a

    public:
    inline static void/*Cseréld LEnum-al ha lesz*/ init() {
      state.states.reserve(10);
      stateCleaners.reserve(10);
    }

    template<System S>
    inline static void regSystem(S& sys) {
      state.states.push_back(std::monostate());
      sys.setup(state.states);
      stateCleaners.push_back([&sys]() {sys.cleanup();});
      sys.id = state.states.size() -1;
    }

    template<System... Systems>
    inline static void regSystem(Systems&... systems) {
      (regSystem(systems), ...);
    }
    
    struct RunSchema {
    // NE KOMPLIKÁLD TÚL.
    // Egyetlen célja hogy ne kelljen .beginFrame stb
      
      // Jelenleg ennyire van szükség
      std::function<bool()> condition = [] {return false;};
      std::function<void()> frame     = [] {};
      
    };
    inline static void run(const RunSchema& schema) {
      while (schema.condition()) {
        schema.frame();
      }
    }

    inline static void cleanup() {
      for (auto& cleaner : stateCleaners) {
        cleaner();
      }
    }

      
  };

}
