#pragma once

#include "common.hpp"
#include "state.hpp"

namespace engine {

  struct Context {

    static Context init();
    // Ez nem tud a használatról, csak betölti a motort.
    // És visszaad egy új contextust.
    
    struct RunSchema {
      std::function<void()> frame = nullptr;
    };
    int run(const RunSchema& schema);
    
    // Ezeket a függvényeket használhassa a lambdaban
    L::Result draw();

    private:
    
    L::Result setup();
    // Beállításk alapján felállít dolgokat
    
    L::Result running();


    L::Result cleanup();
    

    State state;
  };

}
