#include <engine/engine.hpp>

using namespace engine;

L::Result Context::createState(const RendererSchema& schema, RendererHandle& handle) {
  
  this->state.renderers.push_back({.schema = schema}); 
  handle.id = this->state.renderers.size() -1;

  return engine::L::Result::SUCCESS;
}

// ... és a többi
