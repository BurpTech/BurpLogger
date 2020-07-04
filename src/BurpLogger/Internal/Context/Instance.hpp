#pragma once

#include <array>
#include <cstddef>
#include "Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Context {

      template <size_t transportCount>
      class Instance : public Interface {

        public:

          using Index = size_t;

          Instance(const char * label, const Interface * parent) :
            _label(label),
            _parent(parent)
          {}

          const char * getLabel() const override {
            return _label;
          }

          const Interface * getParent() const override {
            return _parent;
          }

          void setCache(const Index index, const void * cache) {
            _cache[index] = cache;
          }

          const void * getCache(const Index index) const {
            return _cache[index];
          }

        private:

          using Cache = std::array<const void *, transportCount>;

          Cache _cache;
          const char * _label;
          const Interface * _parent;

      };

    }
  }
}
