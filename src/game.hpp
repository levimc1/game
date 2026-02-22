#pragma once

// hogy minden egy compilation unit legyen

#include <engine/engine.hpp>

#define M_RENDERER
#include <engine/renderer/renderer.hpp>
inline renderer::Module* get() { // Itt adjuk hozzá azt amit akarunk.
  static renderer::Module instance = renderer::create();
  return &instance;
}
