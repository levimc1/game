#include <chrono>
#include <game.hpp>
#include <thread>
#include <iostream>
#include <functional>

#include "engine.hpp"
#include "context.hpp"

#define CALL(x) { int _tmp = x; if (_tmp != 0) {return _tmp; }; } ;

using namespace std::chrono_literals;

namespace engine {

  int run(Stage init, Stage pre_tick, Stage tick, Stage frame, Stage cleanup, std::chrono::milliseconds tick_time) {
      
    for (auto fn : init.fns) {
      CALL(fn()); 
    }
    
    using Clock = std::chrono::steady_clock;
    using ms = std::chrono::milliseconds;
    auto last_frame = Clock::now();

    while (!should_shutdown) {
      auto now = Clock::now();
      std::chrono::duration<float> dt_dur = now - last_frame;
      delta_time = dt_dur.count();
      last_frame = now;
      
      for (auto& fn : pre_tick.fns) {
        CALL(fn()); // pld input
      }
      for (auto& fn : tick.fns) {
        CALL(fn()); // sim
      }
      for (auto& fn : frame.fns) {
        CALL(fn()); // renderer-ek izéje.
      }

      // várjunk a kövektező frame-re, jelenleg csak wait, de lehetne erre is pár minimális motor task
      // pld: nem tudom, ecs memória vmi?
      auto frame_end = Clock::now();
      auto work_time = std::chrono::duration_cast<ms>(frame_end - now); 
      if (tick_time != 0ms) {
        if (work_time < tick_time) {
          std::this_thread::sleep_for(tick_time - work_time); // kb, de senkit nem érdekel.
        } else {
          std::cout << "Frame túlidő" << std::endl;
        }
      }

      ticks++;
    }

    for (auto fn : cleanup.fns) {
      CALL(fn());
    }

    return 0;
  }
}
