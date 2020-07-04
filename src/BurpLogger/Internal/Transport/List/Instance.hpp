#pragma once

#include <array>
#include <cstddef>
#include "../Interface.hpp"
#include "Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {
      namespace List {

        template <size_t transportCount>
        class Instance : public Interface {

          public:

            using Transports = std::array<Transport::Interface *, transportCount>;

            Instance(const Transports & transports) :
              _transports(transports)
            {}

            void log(const Entry::Interface & entry) const {
              for (auto transport : _transports) {
                transport->log(entry);
              }
            }

          private:

            const Transports & _transports;

        };

      }
    }
  }
}
