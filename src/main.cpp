#include <engine/Renderer.hpp>
#include <engine/SpriteRenderer2D.hpp>
#include <engine/registry.hpp>

int main() {

  auto& renderer = instance<Renderer>();
  auto& srenderer = instance<SpriteRenderer2D>();
  
  renderer.setup();
  srenderer.setup();

  while (!glfwWindowShouldClose(renderer.window)) {

    renderer.preDraw();
    srenderer.draw();
    renderer.postDraw();
  }

  renderer.cleanup();
}
