#pragma once

#include "Internal/Transport/Interface.hpp"
#include "Internal/Transport/List/Instance.hpp"

namespace BurpLogger {

  using Transport = Internal::Transport::Interface;

  template <size_t transportCount>
  using TransportList = Internal::Transport::List::Instance<transportCount>;

}
