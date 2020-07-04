#pragma once

#include "Internal/Factory/Instance.hpp"
#include <cstddef>

namespace BurpLogger {

  template <size_t messageSize, size_t transportCount, size_t loggerCount>
  using Factory = Internal::Factory::Instance<messageSize, transportCount, loggerCount>;

}
