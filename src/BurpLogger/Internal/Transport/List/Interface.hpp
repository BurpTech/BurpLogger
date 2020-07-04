#pragma once

#include "../../Context.hpp"
#include "../../Entry/Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {
      namespace List {

        class Interface {

          public:

            virtual void log(const Context & context, const Entry::Interface & entry) const = 0;

        };

      }
    }
  }
}
