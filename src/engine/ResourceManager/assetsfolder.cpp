#include "../ResourceManager.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::filesystem::path ResourceManager::getAssetsFolder() {

  char buf[4096];

#ifdef _WIN32
  GetModuleFileNameA(NULL, buf, sizeof(buf));
#else
  ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
  if (len == -1)
    throw std::runtime_error("ShaderLoader: /proc/self/exe unreadable");
  buf[len] = '\0';
#endif
  
  std::filesystem::path exeDir = std::filesystem::path(buf).parent_path();
  return (exeDir / ".." / "src" / "assets"); 
}
