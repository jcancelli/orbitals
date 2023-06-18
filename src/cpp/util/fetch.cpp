#include "fetch.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>

#include <iostream>

namespace orbitals {

namespace util {

std::string fetch_string(const std::string& url) {
  char** buffer = nullptr;
  int size, error;
  emscripten_wget_data(url.c_str(), (void**)buffer, &size, &error);
  if (error != 0) {
    std::cout << "Error while fetching string from " << url << "\n";
    assert(false);
  }
  std::string data(*buffer, size);
  free(*buffer);
  return data;
}

FetchedBuffer::~FetchedBuffer() {
  free(this->data);
}

FetchedBuffer fetch_bytes(const std::string& url) {
  FetchedBuffer result;
  int error;
  emscripten_wget_data(url.c_str(), (void**)&(result.data), &(result.size), &error);
  if (error != 0) {
    std::cout << "Error while fetching bytes from " << url << "\n";
    assert(false);
  }
  return result;
}

}  // namespace util

}  // namespace orbitals