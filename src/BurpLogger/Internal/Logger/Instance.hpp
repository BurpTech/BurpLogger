#pragma once

#include <array>
#include <cstddef>
#include "../Entry/Instance.hpp"
#include "../Transport/List.hpp"
#include "../Context/Instance.hpp"
#include "../Factory/Interface.hpp"
#include "Interface.hpp"

#define BURP_LOGGER_LEVEL_OVERRIDES(LEVEL)\
  void LEVEL(const char * format, va_list args) const override {\
    log(Level::LEVEL, format, args);\
  }\
  void LEVEL(const char * format, ...) const override {\
    va_list args;\
    va_start(args, format);\
    log(Level::LEVEL, format, args);\
    va_end(args);\
  }

namespace BurpLogger {
  namespace Internal {
    namespace Logger {

      template <size_t messageSize, size_t transportCount>
      class Instance : public Interface {

        public:

          using Entry = Entry::Instance<messageSize>;
          using TransportList = Transport::List<transportCount>;
          using Context = Context::Instance<transportCount>;

          Instance(
              Context * context,
              const TransportList & transportList,
              Factory::Interface * factory
          ) :
            _context(context),
            _transportList(transportList),
            _factory(factory)
          {
            _transportList.cache(_context);
          }

          const Interface * create(const char * label) const override {
            return _factory->create(label, _context);
          }

          void log(const Level::Level level, const char * format, va_list args) const override {
            if (_factory->getLevel() >= level) {
              const Entry entry(level, format, args);
              _transportList.log(_context, entry);
            }
          }

          void log(const Level::Level level, const char * format, ...) const override {
            va_list args;
            va_start(args, format);
            log(level, format, args);
            va_end(args);
          }

          void log(const char * label, const BurpStatus::Status & status) const override {
            switch (status.getLevel()) {
              case BurpStatus::Status::Level::INFO:
                info("%s: %s", label, status.c_str());
                break;
              case BurpStatus::Status::Level::WARNING:
                warn("%s: %s", label, status.c_str());
                break;
              case BurpStatus::Status::Level::ERROR:
                error("%s: %s", label, status.c_str());
                break;
            }
          };

          BURP_LOGGER_LEVEL_OVERRIDES(always)
          BURP_LOGGER_LEVEL_OVERRIDES(error)
          BURP_LOGGER_LEVEL_OVERRIDES(warn)
          BURP_LOGGER_LEVEL_OVERRIDES(info)
          BURP_LOGGER_LEVEL_OVERRIDES(verbose)
          BURP_LOGGER_LEVEL_OVERRIDES(debug)
          BURP_LOGGER_LEVEL_OVERRIDES(silly)

        private:

          Context * _context;
          const TransportList & _transportList;
          Factory::Interface * _factory;

      };

    }
  }
}
