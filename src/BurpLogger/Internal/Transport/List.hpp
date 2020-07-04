#pragma once

#include <array>
#include <cstddef>
#include "Interface.hpp"
#include "../Context/Instance.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Transport {

      template <size_t transportCount>
      class List {

        public:

          using Transports = std::array<Transport::Interface *, transportCount>;
          using Context = Internal::Context::Instance<transportCount>;
          using Index = typename Context::Index;

          List(const Transports & transports) :
            _transports(transports)
          {}

          void cache(Context * context) const {
            for (Index index = 0; index < transportCount; index++) {
              context->setCache(index, _transports[index]->cache(context));
            }
          }

          void log(const Context * context, const Entry::Interface & entry) const {
            for (Index index = 0; index < transportCount; index++) {
              _transports[index]->log(context->getCache(index), entry);
            }
          }

        private:

          const Transports & _transports;

      };

    }
  }
}
