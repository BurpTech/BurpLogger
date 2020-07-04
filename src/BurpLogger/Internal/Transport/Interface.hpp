#pragma once

#include "../Context/Interface.hpp"
#include "../Entry/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {

      class Interface {

        public:

          virtual const void * cache(const Context::Interface * context) = 0;
          virtual void log(const void * cache, const Entry::Interface & entry) = 0;

      };

    }
  }
}
