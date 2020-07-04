#pragma once

#include <stdarg.h>
#include "../Level.hpp"

#define BURP_LOGGER_LEVEL_VIRTUALS(LEVEL)\
  virtual void LEVEL(const char * format, va_list args) const = 0;\
  virtual void LEVEL(const char * format, ...) const = 0;

namespace BurpLogger {
  namespace Internal {
    namespace Logger {

      class Interface {

        public:

          virtual const Interface * create(const char * label) const = 0;

          virtual void log(Level::Level level, const char * format, va_list args) const = 0;
          virtual void log(Level::Level level, const char * format, ...) const = 0;

          BURP_LOGGER_LEVEL_VIRTUALS(error)
          BURP_LOGGER_LEVEL_VIRTUALS(warn)
          BURP_LOGGER_LEVEL_VIRTUALS(info)
          BURP_LOGGER_LEVEL_VIRTUALS(verbose)
          BURP_LOGGER_LEVEL_VIRTUALS(debug)
          BURP_LOGGER_LEVEL_VIRTUALS(silly)

      };

    }
  }
}
