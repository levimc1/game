#pragma once

#include <engine/registry.hpp>

#include <filesystem>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

#include <extern/glm/glm.hpp>


struct ResourceManager {

  struct Atlas {

    int width, height, channels;
    std::vector<uint8_t> data;

  };
  
  using TextureID = uint32_t;
  struct Texture {

    glm::vec2 startPos;
    glm::vec2 resolution;

  };
  
  static constexpr unsigned int MAX_FRAMES = 16;
  struct Animation {
    
    uint8_t size;
    TextureID frames[MAX_FRAMES] = {};

  };

  Atlas atlas;
  std::vector<Texture> textures;
  std::vector<Animation> animations;

  std::unordered_map<std::string, size_t> textureLookup;
  std::unordered_map<std::string, size_t> animationLookup;

  void loadAtlas(const std::string& path);
  void loadTextures(const std::string& path);
  void loadAnimations(const std::string& path);
  
  static std::filesystem::path getAssetsFolder();

};
