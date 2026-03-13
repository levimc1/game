#pragma once

#include "extern/glm/glm.hpp"
#include <unordered_map>

namespace engine::internal {
  
  struct Block {
    enum class BlockType {
      RED, GREEN, BLUE
    } type;
  };

  struct Chunk {
    Block blocks[4096]; // 16 ^ 3
  };
  
  // AI Hashe
  struct IVec3Hash {
    std::size_t operator()(const glm::ivec3& v) const {
      std::size_t seed = 0;
      for (int32_t c : {v.x, v.y, v.z}) {
        seed ^= std::hash<int32_t>{}(c) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };

  struct ChunkRendererState {
    std::unordered_map<glm::ivec3, Chunk, IVec3Hash> chunks;
  }; 
}
