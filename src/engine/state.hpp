#pragma once

// Circular dependecy elkerülésére. 

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <cassert>

// Összes state típus 
/*
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

}*/

/*namespace engine::internal {
  
  // Statikus főleg.
  namespace EngineState {
  // State csak adat. Nem kellenek hookok, végül töröltem run()-t mert lassú, nem kontrollálod. stb.
    
    // kivéve ez. sajnos ez kell, faszomat.
    *
    template<typename T>
    concept Hook = requires (T& t) {
      t.setup();
      // t...
      t.cleanup();
    };
    // Faszomat. Ez csak manuális setup és cleanup elkerülésére, minden mást te oldol.
    template<typename T>
    concept SystemHook = requires (T& t) {
      t.setup();
      t.cleanup();
    };/
    // Jobb megoldás erre. 
    // Jelenleg még üres, de kellhet.
    struct SystemDesc {
      
    };
    using SystemStateID = size_t;
    //
    template<typename T>
    concept System = requires (T& t) {
      (t.desc) -> SystemDesc;
      (t.id) -> SystemStateID;
    };
    // És opcionális hookok. Erre lehet kellessz majd macro. de most lusta vagyok
    template<typename T>
    concept HasSetupHook = requires (T& t) {
      t.setup;
    };
    template<typename T>
    concept HasCleanupHook = requires (T& t) {
      t.cleanup;
    };

    template<System T>
    inline std::vector<T>& getStates() {
      static std::vector<T> states;
      return states;
    }

    template<System T>
    inline T& getState(size_t id) {
      std::vector<T>& states = getStates<T>();
      // hiba ha túl van, pld
      assert(id < states.size()); // (fordítótt)
      return states[id];
    }
    
    // Ezek helytelenek, kezdj vele valamit.
    template<HasSetupHook T>
    inline std::vector<T*>& getHooks() {
      static std::vector<T*> hooks;
      return hooks;
    }

    template<HasSetupHook T>
    inline void addHook(T& hook) {
      std::vector<T*>& hooks = getHooks<T>();
      hooks.push_back(&hook);
    }
    
    template<typename T>
    requires System<T> // hogy T system legyen
    inline void regState(T& system) {
      if constexpr (HasSetupHook<T>) {
        addHook(system);
      }
      if constexpr (HasCleanupHook<T>) {
        addHook(system);
      }
    }
    
    // SHaredhez nincsenek nagy elvárásáink xd
    template<typename T>
    inline T& getShared() {
      static T shared;
      return shared;
    }

  };

}*/

namespace engine::internal {
  
  struct SystemDesc {
      
    std::string name;
    uint32_t hooks = 0;

    static constexpr uint32_t Setup     = 1 << 0;
    static constexpr uint32_t Cleanup   = 1 << 1;
    static constexpr uint32_t PreFrame  = 1 << 2;
    static constexpr uint32_t PostFrame = 1 << 3;

    SystemDesc() = delete;
    SystemDesc(std::string name, uint32_t hooks = 0)
        : name(std::move(name)), hooks(hooks) {}
  };

  // Kicsit OOP. de sajnos erre jutottam :(
  struct System {
      
    size_t id;
    SystemDesc desc; 

    virtual void makeState() = 0;
    // id = engine::internal::EngineState::makeState<Te state típusod>(Kezdőállapot)  
    
    virtual void setup() {};
    virtual void cleanup() {};
    virtual void preFrame() {};
    virtual void postFrame() {};

    System(SystemDesc d) : desc(d) {}

  };

  struct Shared {
      
    // Fogalmam sincs. talán Desc
    SystemDesc desc;

    virtual void setup() {};
    virtual void cleanup() {};
    virtual void preFrame() {};
    virtual void postFrame() {};

    Shared(SystemDesc d) : desc(d) {}
  };
    
  struct EngineState {
    
    // Bővítsd, am nem kötelezp
    
    // STATE 
    template<typename T>
    inline static std::vector<T>& getStates() {
      static std::vector<T> states;
      return states;
    }

    template<typename T>
    inline static T& getState(size_t id) {
      std::vector<T>& states = getStates<T>();
      // hiba ha túl van, pld
      assert(id < states.size()); // (fordítótt)
      return states[id];
    }

    template<typename T>
    inline static size_t makeState(T& state) {      
      std::vector<T>& states = getStates<T>();
      states.push_back(state); // size = 0 -> 1, 121 -> 122 
      return states.size() - 1; 
    } // garantálja hogy getState(id) azt adja vissza.
    
    template<typename T>
    inline static size_t makeState() {
      std::vector<T>& states = getStates<T>();
      states.emplace_back();
      return states.size() - 1;
    }
    
    //inline static std::vector<Shared*> sharedSetupHooks;
    enum class HookType {Setup, Cleanup, PreFrame, PostFrame}; // ...
                                          //

    template<typename T, HookType type>
    requires (std::same_as<T, System> || std::same_as<T, Shared>)
    inline static std::vector<T*>& getHooks() {
      static std::vector<T*> hooks;
      return hooks;
    }

    template<typename T>
    requires std::derived_from<T, Shared>
    inline static T& getShared() {
      static T shared;
      return shared;
    }

    template<typename T>
    requires std::derived_from<T, Shared>
    inline static void regShared() {
      static bool registered = false;
      T& shared = getShared<T>(); // constructor
      if (!registered) {
        if (shared.desc.hooks & SystemDesc::Setup)
          getHooks<Shared, HookType::Setup>().push_back(&shared);  

        if (shared.desc.hooks & SystemDesc::Cleanup)
          getHooks<Shared, HookType::Cleanup>().push_back(&shared);  

        if (shared.desc.hooks & SystemDesc::PreFrame)
          getHooks<Shared, HookType::PreFrame>().push_back(&shared);  

        if (shared.desc.hooks & SystemDesc::PostFrame)
          getHooks<Shared, HookType::PostFrame>().push_back(&shared);  

        registered = true;
      }
    }

    template<typename T>
    requires std::derived_from<T, System>
    inline static void regSystem(T& system) {
      if (system.desc.hooks & SystemDesc::Setup)
        getHooks<System, HookType::Setup>().push_back(&system);

      if (system.desc.hooks & SystemDesc::Cleanup)
        getHooks<System, HookType::Cleanup>().push_back(&system);

      if (system.desc.hooks & SystemDesc::PreFrame)
        getHooks<System, HookType::PreFrame>().push_back(&system);  

      if (system.desc.hooks & SystemDesc::PostFrame)
        getHooks<System, HookType::PostFrame>().push_back(&system);  
      // ...
      system.makeState();
    }

    // MInden külön tárolva. így lehet problámák lesznek valahol :=/
  };

}
