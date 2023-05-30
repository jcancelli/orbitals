#include "fs.hpp"

#include <cassert>
#include <fstream>
#include <sstream>

namespace orbitals {

namespace util {

std::string read_string(std::string const& path) {
  std::ifstream file(path);
  std::stringstream content;
  assert(file.is_open());
  content << file.rdbuf();
  return content.str();
}

}  // namespace util

}  // namespace orbitals
