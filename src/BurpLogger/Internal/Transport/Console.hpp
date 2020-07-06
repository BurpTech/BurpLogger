#pragma once

#include "Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {

      class Console : public Interface {

        public:

          const void * cache(const Context::Interface * context) override;
          void log(const void * cache, const Entry::Interface & entry) override;

        private:

          static void _printLevel(const Level::Level level);
          static void _printContext(const Context::Interface * context);

      };

    }
  }
}
