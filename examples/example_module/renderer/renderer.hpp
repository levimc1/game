#pragma once

#include <game.hpp>

#if defined(M_RENDERER) 
// file ami összegyűjt mindent a renderer modultól

// dependenciák!
// #define M_VMI

#include "context.hpp"

namespace renderer {
  
  struct Module {
    Context ctx;
    
    // Beállítások a játéktól.
    // De ezeknek nem kell.
  };
  
  // stage-ek.
  int init();

  // api-ok

  Module* get();
  Module create(); // Igenis kellenek paraméterek..

}
#endif
