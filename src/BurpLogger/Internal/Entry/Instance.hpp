#pragma once

#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include "Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Entry {

      template <size_t messageSize>
      class Instance : public Interface {

        public:

          Instance(const Labels * labels, const Level::Level level, const char * format, va_list args) :
            _labels(labels),
            _level(level)
          {
            vsnprintf(_message, messageSize, format, args);
          }

          const Labels * getLabels() const {
            return _labels;
          }

          const Level::Level getLevel() const {
            return _level;
          }

          const char * getMessage() const {
            return _message;
          }

        private:

          const Labels * _labels;
          const Level::Level _level;
          char _message[messageSize];

      };

    }
  }
}
