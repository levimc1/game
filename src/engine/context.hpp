#pragma once

#include "state.hpp"
#include <concepts>
#include <cstdint>
#include <functional>
#include <vector>

namespace engine {

  template<typename T>
  concept System = requires(T t, State& s) {
    { t.id } -> std::same_as<size_t&>;
    t.setup(s);
    t.cleanup();
  };

  struct Context {
    
    private:
    static std::vector<State> states;
    static std::vector<std::function<void()>> stateCleaners;
    // csak cleanup, frame 0%-a

    public:
    inline static void/*Cseréld LEnum-al ha lesz*/ init() {
      states.reserve(10);
      stateCleaners.reserve(10);
    }

    template<System S>
    inline static void regSystem(S& sys) {
      states.push_back(std::monostate());
      sys.setup(states.back());
      stateCleaners.push_back([&sys]() {sys.cleanup();});
      sys.id = states.size() -1;
    }

    template<S&... Systems>
    inline static void regSystem(Ss&... systems) {
      (regSystem(systems), ...);
    }
    
    struct RunSchema {
    // NE KOMPLIKÁLD TÚL.
    // Egyetlen célja hogy ne kelljen .beginFrame stb
      
      // Jelenleg ennyire van szükség
      std::function<void()> condition = [] {return false;};
      std::function<void()> frame     = [] {};
      
    };
    inline static void run(const RunSchema& schema) {
      while (schema.condition) {
        schema.frame();
      }
    }

    inline static void cleanup() {
      for (auto& cleaner : stateCleaners) {
        cleaner();
      }
    }

    inline static State& getState(size_t index) {return states[index];}
      
  };

}
