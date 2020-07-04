#pragma once

#include "../Level.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Entry {

      class Interface {

        public:

          virtual const Level::Level getLevel() const = 0;
          virtual const char * getMessage() const = 0;

      };

    }
  }
}
