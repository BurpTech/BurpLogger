#pragma once

#include <array>
#include <cstddef>
#include "../Entry/Instance.hpp"
#include "../Transport/List/Interface.hpp"
#include "Interface.hpp"

#define BURP_LOGGER_LEVEL_OVERRIDES(LEVEL)\
  void LEVEL(const char * format, va_list args) override {\
    log(Level::LEVEL, format, args);\
  }\
  void LEVEL(const char * format, ...) override {\
    va_list args;\
    va_start(args, format);\
    log(Level::LEVEL, format, args);\
    va_end(args);\
  }

namespace BurpLogger {
  namespace Internal {
    namespace Logger {

      template <size_t messageSize>
      class Instance : public Interface {

        public:

          using Entry = Entry::Instance<messageSize>;

          Instance(const char * label, const Transport::List::Interface & transportList) :
            _context(label),
            _transportList(transportList)
          {}

          Instance(const char * label, Interface & parent) :
            _context(label, &(parent.getContext())),
            _transportList(parent.getTransportList())
          {}

          const Context & getContext() const override {
            return _context;
          }

          const Transport::List::Interface & getTransportList() const override {
            return _transportList;
          }

          void log(Level::Level level, const char * format, va_list args) override {
            const Entry entry(level, format, args);
            _transportList.log(_context, entry);
          }

          void log(Level::Level level, const char * format, ...) override {
            va_list args;
            va_start(args, format);
            log(level, format, args);
            va_end(args);
          }

          BURP_LOGGER_LEVEL_OVERRIDES(error)
          BURP_LOGGER_LEVEL_OVERRIDES(warn)
          BURP_LOGGER_LEVEL_OVERRIDES(info)
          BURP_LOGGER_LEVEL_OVERRIDES(verbose)
          BURP_LOGGER_LEVEL_OVERRIDES(debug)
          BURP_LOGGER_LEVEL_OVERRIDES(silly)

        private:

          const Context _context;
          const Transport::List::Interface & _transportList;

      };

    }
  }
}
