#pragma once

#include "../Entry/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {

      class Interface {

        public:

          virtual void log(const Entry::Interface & entry) = 0;

      };

    }
  }
}
