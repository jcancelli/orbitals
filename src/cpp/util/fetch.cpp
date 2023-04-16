#include "fetch.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>

#include <iostream>

namespace orbitals {

namespace util {

EM_ASYNC_JS(const char*, _fetch_string, (const char* url), {
  const _url = UTF8ToString(url);
  const data = await fetch(_url).then(function(res) { return res.text(); });
  const stringLength = lengthBytesUTF8(data) + 1;
  const stringPointer = _malloc(stringLength);
  stringToUTF8(data, stringPointer, stringLength);
  return stringPointer;
});

std::string fetch_string(const std::string& url) {
  auto* cString = _fetch_string(url.c_str());
  std::string string(cString);
  free((void*)cString);
  return string;
}

FetchedBuffer::~FetchedBuffer() {
  free(this->data);
}

EM_ASYNC_JS(unsigned char*, _fetch_bytes, (const char* url, int* size), {
  const _url = UTF8ToString(url);
  const data = await fetch(_url).then(function(res) { return res.arrayBuffer(); });
  const bufferSize = data.byteLength;
  const bufferPointer = _malloc(bufferSize);
  setValue(size, bufferSize, "i32");
  HEAPU8.set(new Uint8Array(data), bufferPointer);
  return bufferPointer;
});

FetchedBuffer* fetch_bytes(const std::string& url) {
  FetchedBuffer* result = new FetchedBuffer;
  result->data = _fetch_bytes(url.c_str(), &result->size);
  return result;
}

}  // namespace util

}  // namespace orbitals