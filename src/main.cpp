#include "engine/engine.hpp"
#include <chrono>
#include <iostream>

#include <game.hpp>

int main() {

  std::cout << "Hello, world!" << std::endl;

  engine::run(
      Stage{&renderer::init}, 
      Stage{}, 
      Stage{}, 
      Stage{&renderer::draw}, 
      Stage{renderer::cleanup}, 
      std::chrono::milliseconds(16)
      );

}
