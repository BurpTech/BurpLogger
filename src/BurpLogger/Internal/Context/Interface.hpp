#pragma once

namespace BurpLogger {
  namespace Internal {
    namespace Context {

      class Interface {

        public:

          virtual const char * getLabel() const = 0;
          virtual const Interface * getParent() const = 0;

      };

    }
  }
}
