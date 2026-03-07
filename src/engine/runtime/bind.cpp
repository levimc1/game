#include <engine/context.hpp>

using namespace engine;

L::Result Context::pushBind(const RendererHandle& handle) {
  
  this->state.rendererBindStack.push_back(handle.id);

  return L::Result::SUCCESS;
}

// ...

L::Result Context::popBind(L::State stack) {
  
  switch (stack) {
    case L::State::Renderer:
      this->state.rendererBindStack.pop_back();
    // ...
  }
  return L::Result::SUCCESS;
}

L::Result Context::clearBind(L::State stack) {
  
  switch (stack) {
    case L::State::Renderer:
      this->state.rendererBindStack.clear();
    // ...
  }
  return L::Result::SUCCESS;
}

L::Result Context::clearAllBind() {
  
  State& state = this->state;

  state.rendererBindStack.clear();
  // ...

  return L::Result::SUCCESS;
}
