#pragma once

#include "Internal/Logger/Instance.hpp"

namespace BurpLogger {
  template <size_t messageSize>
  using Logger = Internal::Logger::Instance<messageSize>;
}
