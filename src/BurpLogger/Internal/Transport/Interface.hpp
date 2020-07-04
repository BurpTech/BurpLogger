#pragma once

#include "../Context.hpp"
#include "../Entry/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {

      class Interface {

        public:

          virtual void log(const Context & context, const Entry::Interface & entry) = 0;

      };

    }
  }
}
