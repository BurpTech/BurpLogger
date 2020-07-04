#pragma once

#include "../Logger/Interface.hpp"
#include "../Context/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Factory {

      class Interface {

        public:

          virtual const Logger::Interface * create(const char * label, const Context::Interface * context) = 0;
      };

    }
  }
}
