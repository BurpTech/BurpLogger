#pragma once

#include "../Logger/Interface.hpp"
#include "../Context/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Factory {

      class Interface {

        public:

          virtual const Logger::Interface * create(const char * label, const Context::Interface * context) = 0;
          virtual const Level::Level getLevel() const = 0;
          virtual const size_t getCount() const = 0;
          virtual const bool maxExceeded() const = 0;

      };

    }
  }
}
