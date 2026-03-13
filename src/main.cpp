#include "engine/context.hpp"
#include "engine/engine.hpp"
#include <print>

using namespace engine;

int main() {

  std::println("Hello, {}", "World!");
  
  Context::init();

  TestRenderer renderer{    
  };

  Context::regSystem(renderer);

  Context::run({
    .condition = {[&](){
      return renderer.condition(); 
    }},
    .frame = {[&](){
      renderer.draw();
    }}
  });

  return 0;
}
