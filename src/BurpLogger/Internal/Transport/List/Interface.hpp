#pragma once

#include "../../Entry/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {
      namespace List {

        class Interface {

          public:

            virtual void log(const Entry::Interface & entry) const = 0;

        };

      }
    }
  }
}
