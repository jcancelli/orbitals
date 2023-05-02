#pragma once

#include <iostream>

#define ASSERT(condition, message)                                                           \
  if (!(condition)) {                                                                        \
    std::cerr << "----------\n[Failed assert]\nFile: " << __FILE__ << "\nLine: " << __LINE__ \
              << "\nMessage: " << message << "\n----------\n";                               \
    assert(condition);                                                                       \
  }