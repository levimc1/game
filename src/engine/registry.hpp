#pragma once

template<typename T>
inline T& instance() {
  static T inst;
  return inst;
}
