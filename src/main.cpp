#include "engine/engine.hpp"
//#include <print>

using namespace engine;

int main() {

  //std::println("Hello, {}", "World!");
  
  //TestRenderer renderer{};
  SpriteRenderer2D renderer{};

  Context::regSystem(renderer);

  Context::run(Context::RunSchema{
    .running = [&](){
      return renderer.condition(); 
    },
    .frame = [&](){
      renderer.draw();
    }
  });

  return 0;
}
