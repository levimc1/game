#include "../ResourceManager.hpp"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <extern/stb_image.h>


// jövőbe helperbe
void trim(std::string& str) {

  str.erase(0, str.find_first_not_of(" \t"));
  str.erase(str.find_last_not_of(" \t")  + 1);
}

void ResourceManager::loadAtlas(const std::string& path) {
  
  unsigned char* raw = stbi_load(path.c_str(), &atlas.width, &atlas.height, &atlas.channels, 0);
  if (!raw)
    throw std::runtime_error("Atlas betöltése sikertelen: " + path);

  atlas.data.assign(raw, raw + atlas.width * atlas.height * atlas.channels); 
  // Betölti raw-ot raw tól (kezdet) a végéig.
  
  stbi_image_free(raw);
}

void ResourceManager::loadTextures(const std::string& path) {
  
  std::ifstream file(path);
  if (!file)
    throw std::runtime_error("Nem sikerült megnyitni textúra file-t: " + path);
  
  std::string line;
  while (std::getline(file, line)) {
    char name[64];
    Texture t{};
    // C standard.
    sscanf(line.c_str(), "%63[^:]: %d,%d %d,%d", name, &t.startPos.x, &t.startPos.y, &t.resolution.x, &t.resolution.y);
    // Keress max 63 karaktert :-ig, majd olvasd be az értékeket a változókba
    // Fontos, 63 mert terminátor karakter is kell. 
    
    textures.push_back(t);
    textureLookup[name] = textures.size() -1;
  }
}

void ResourceManager::loadAnimations(const std::string& path) {
  
  if (animations.empty()) {
    animations.push_back(Animation{});
  } // nem tudom hogy garbage-e, de ez a kimaradó.

  std::ifstream file(path);
  if (!file) 
    throw std::runtime_error("Nem sikerült megnyitni animáció file-t: " + path);
  
  std::string line;
  while (std::getline(file, line)) {
    // C++ itt egyszerűbb
    std::istringstream ss(line);
    Animation a;

    std::string name;
    std::getline(ss, name, ':');
    
    std::string frame;
    int i = 0;
    while (std::getline(ss, frame, ',')) {
      trim(frame);
      a.frames[i] = (textureLookup[frame]);
      i++;
    }
    a.size = i + 1;
    animations.push_back(a);
    animationLookup[name] = animations.size() -1;
  }
}
