#include "engine/engine.hpp"

using namespace engine;

int main() {
  
  Context e = Context::init();
  
  RendererHandle renderer;
  e.createState({}, renderer);

  return e.run({
      .frame = [&]() {
        e.pushBind(renderer);
        e.draw();            
        e.popBind(L::State::Renderer);;
      }
    });
}
