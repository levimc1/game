#pragma once

#include "state.hpp"
#include <concepts>
#include <cstdint>
#include <functional>
#include <print>
#include <vector>

/*
namespace engine {

  template<typename T>
  concept System = requires(T t, std::vector<State>& s) {
    { t.id } -> std::same_as<size_t&>;
    t.useShareds();
    t.setup(s);
    t.cleanup();
  };

  struct Context {
    
    private:
    inline static internal::EngineState state;
    inline static std::vector<std::function<void()>> stateSetuppers;
    inline static std::vector<std::function<void()>> stateCleaners;

    public:
    inline static void/*Cseréld LEnum-al ha lesz init() {
      state.states.reserve(10);
      stateCleaners.reserve(10);
      stateSetuppers.reserve(10);
    }

    template<System S>
    inline static void regSystem(S& sys) {
      state.states.push_back(std::monostate());
      stateSetuppers.push_back([&sys]() {sys.setup(state.states);});
      stateCleaners.push_back([&sys]() {sys.cleanup();});
      sys.id = state.states.size() -1;
      sys.useShareds();
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
      for (auto& hook : internal::EngineSharedState::setupHooks) {
        hook();
      }
      for (auto& setupper : stateSetuppers) {
        setupper();
      }
      while (schema.condition()) {
        for (auto& hook : internal::EngineSharedState::beginFrameHooks) {
          hook();
        }
        schema.frame();
        for (auto& hook : internal::EngineSharedState::endFrameHooks) {
          hook();
        }
      }
      for (auto& cleaner : stateCleaners) {
        cleaner();
      }
      for (auto& hook : internal::EngineSharedState::cleanupHooks) {
        hook();
      }
    
    }

  };

}*/

namespace engine {

  struct Context {
    
    template<typename T> 
    requires std::derived_from<T, internal::System>
    inline static void regSystem(T& system) {
      internal::EngineState::regSystem(system);
    } // mert így kényelmesebb
    

    struct RunSchema {
      std::function<bool()> running;
      std::function<void()> frame;
    };

    inline static void run(const RunSchema& schema) {
      for ( auto& shared : internal::EngineState::getHooks<internal::Shared, internal::EngineState::HookType::Setup>() )
        shared->setup();
      for ( auto& system : internal::EngineState::getHooks<internal::System, internal::EngineState::HookType::Setup>() )
        system->setup();

      
      while (schema.running()) {
        for ( auto& shared : internal::EngineState::getHooks<internal::Shared, internal::EngineState::HookType::PreFrame>() )
          shared->preFrame();
        for ( auto& system : internal::EngineState::getHooks<internal::System, internal::EngineState::HookType::PreFrame>() )
          system->preFrame();

        schema.frame();

        for ( auto& system : internal::EngineState::getHooks<internal::System, internal::EngineState::HookType::PostFrame>() )
          system->postFrame();
        for ( auto& shared : internal::EngineState::getHooks<internal::Shared, internal::EngineState::HookType::PostFrame>() )
          shared->postFrame();
      }
    
      for ( auto& system : internal::EngineState::getHooks<internal::System, internal::EngineState::HookType::Cleanup>() )
        system->cleanup();
      for ( auto& shared : internal::EngineState::getHooks<internal::Shared, internal::EngineState::HookType::Cleanup>() )
        shared->cleanup();

    } 

  };

}
