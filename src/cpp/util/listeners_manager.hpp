#pragma once

#include <map>
#include <type_traits>

namespace orbitals {

namespace util {

template <class T>
class ListenersManager {
 public:
  using Listener = std::function<void(T)>;

 private:
  unsigned m_NextID;
  std::map<unsigned, Listener> m_Listeners;

 public:
  unsigned addListener(Listener const& listener);
  void removeListener(unsigned listenerID);
  void notifyListeners(T& value) const;
};

}  // namespace util

}  // namespace orbitals

#include "listeners_manager.inl"
