#pragma once

#ifdef M_RENDERER 

#include "context.hpp"

namespace renderer {

  struct Module {
    
    Context ctx;

  };
  // globális eléréshez.
  extern Module* instance;

}

#endif
