#pragma once

#include "common.hpp"
#include "engine/states/renderer/schema.hpp"
#include "state.hpp"

#include "states/renderer/handle.hpp"

namespace engine {

  struct Context {

    static Context init();
    // Ez nem tud a használatról, csak betölti a motort.
    // És visszaad egy új contextust.
    
    struct RunSchema {
      std::function<void()> frame;
    };
    int run(const RunSchema& schema);
    
    // Alap funkciók - functions/ mappában az implementáció
    L::Result draw();
    
    // Bindolás

    // schema reference meg fog halni. de jó a renderer.schema = schema, mivel akkor másol
    L::Result createState(const RendererSchema& schema, RendererHandle& handle);
    // ... és több createState Is

    L::Result pushBind(const RendererHandle& handle);
    L::Result popBind(L::State stack);
    L::Result clearBind(L::State stack);
    L::Result clearAllBind();

    // Internális state-ek run()-ban, internal/ és run runtime/ .ben van.
    L::Result setup();
    // Beállításk alapján felállít dolgokat
    
    L::Result running();

    L::Result cleanup();
    
    State state;
  };

}
