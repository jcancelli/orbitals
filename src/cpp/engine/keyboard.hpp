#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace orbitals {

namespace engine {

class Keyboard {
 protected:
  std::unordered_map<std::string, bool> m_State;

 public:
  bool keyIsDown(std::string const& key) const;
  std::vector<std::string> getDownKeys() const;
  void press(std::string const& key);
  void release(std::string const& key);
};

}  // namespace engine

}  // namespace orbitals
