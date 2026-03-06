#include "engine/context.hpp"

using namespace engine;

int main() {
  
  Context e = Context::init();

  return e.run({
      .frame = [&]() {
        e.draw();                 
      }
    });
}
