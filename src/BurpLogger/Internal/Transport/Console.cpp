#include "Console.hpp"

#ifdef BURP_NATIVE
#include "stdio.h"
#define PRINTF printf
#else
#include <Arduino.h>
#define PRINTF Serial.printf
#endif

namespace BurpLogger {
  namespace Internal {
    namespace Transport {

      const void * Console::cache(const Context::Interface * context) {
        return context;
      }

      void Console::log(const void * cache, const Entry::Interface & entry) {
        _printLevel(entry.getLevel());
        _printContext(static_cast<const Context::Interface *>(cache));
        PRINTF(" : %s\n", entry.getMessage());
      }

      void Console::_printLevel(const Level::Level level) {
        switch (level) {
          case Level::none:
            break;
          case Level::error:
            PRINTF("ERROR  : ");
            break;
          case Level::warn:
            PRINTF("WARN   : ");
            break;
          case Level::info:
            PRINTF("INFO   : ");
            break;
          case Level::verbose:
            PRINTF("VERBOSE: ");
            break;
          case Level::debug:
            PRINTF("DEBUG  : ");
            break;
          case Level::silly:
            PRINTF("SILLY  : ");
            break;
          default:
            PRINTF("UNKNOWN: ");
            break;
        }
      }

      void Console::_printContext(const Context::Interface * context) {
        if (context) {
          const Context::Interface * parent = context->getParent();
          _printContext(parent);
          PRINTF("[%s]", context->getLabel());
          context = parent;
        }
      }

    }
  }
}
