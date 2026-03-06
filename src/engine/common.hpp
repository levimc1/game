#pragma once

#include <cstdint>

namespace engine::L {
  
  enum class Result : uint32_t {
    SUCCESS = 1,
    //Ide specifikus hibák.
    STOP = 0, // running() adja vissza
  };

}
