#pragma once

#include <string>

namespace orbitals {

namespace util {

std::string fetch_string(const std::string& url);

struct FetchedBuffer {
  unsigned char* data;
  int size;
  ~FetchedBuffer();
};

FetchedBuffer* fetch_bytes(const std::string& url);

}  // namespace util

}  // namespace orbitals