#pragma once

#include "listeners_manager.hpp"

namespace orbitals {

namespace util {

template <class... T>
unsigned Listeners<T...>::addListener(Listener const& listener) {
  unsigned id = m_NextID++;
  m_Listeners[id] = listener;
  return id;
}

template <class... T>
void Listeners<T...>::removeListener(unsigned listenerID) {
  auto pos = m_Listeners.find(listenerID);
  if (pos != m_Listeners.end()) {
    m_Listeners.erase(pos);
  }
}

template <class... T>
void Listeners<T...>::notifyListeners(T... values) const {
  for (auto const& [listenerID, listener] : m_Listeners) {
    listener(values...);
  }
}

}  // namespace util

}  // namespace orbitals
