#pragma once

#include <engine/registry.hpp>
#include "Renderer.hpp"
#include "ResourceManager.hpp"

struct SpriteRenderer2D {
  
  GLuint VAO, quadVBO, instanceVBO, shaderProgram, quadEBO;
  
  struct Sprite {

    glm::vec2 pos;
    unsigned int layer;

    ResourceManager::TextureID texture;
    ResourceManager::TextureID animation = 0;
    // 0 = semmi.
    
    float scale;
  };

  void setup();
  void draw();

};

