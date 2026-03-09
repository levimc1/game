#include "engine/engine.hpp"
#include <print>

using namespace engine;

int main() {

  std::println("Hello, {}", "World!");
  
  engine::Context::init();


}
