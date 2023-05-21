#pragma once

#include <map>
#include <type_traits>

namespace orbitals {

namespace util {

template <class... T>
class Listeners {
 public:
  using Listener = std::function<void(T...)>;

 private:
  unsigned m_NextID;
  std::map<unsigned, Listener> m_Listeners;

 public:
  unsigned add(Listener const& listener);
  void remove(unsigned listenerID);
  void notify(T... values) const;
};

}  // namespace util

}  // namespace orbitals

#include "listeners_manager.inl"
