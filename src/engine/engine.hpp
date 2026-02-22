#pragma once

#include <cstdint>
#include <functional>
#include <sys/types.h>
#include <vector>
#include <initializer_list>
#include <chrono>

using TaskID = uint64_t;

namespace engine {
  
  struct Stage {
    std::vector<std::function<int()>> fns;

    Stage(std::initializer_list<std::function<int()>> ilist) : fns(ilist) {};

  };

  struct Task {
    std::function<int()> fn;
    uint32_t frequency;
    uint64_t tick;
    bool cancelled = false;

  };
  
  // ötletem sincs mi értelme lehet.
  int run(Stage init, Stage pre_tick, Stage tick, Stage frame, Stage cleanup, std::chrono::milliseconds frame_time);
}
