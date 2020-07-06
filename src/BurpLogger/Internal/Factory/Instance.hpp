#pragma once

#include <cstddef>
#include "../Transport/List.hpp"
#include "../Logger/Instance.hpp"
#include "../Context/Instance.hpp"
#include "Interface.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Factory {

      template <size_t messageSize, size_t transportCount, size_t loggerCount>
      class Instance : public Interface {

        public:

          using TransportList = Transport::List<transportCount>;
          using Transports = typename TransportList::Transports;

          Instance(const Level::Level level, const Transports & transports) :
            _level(level),
            _transportList(transports),
            _count(0)
          {}

          const Logger::Interface * create(const char * label, const Context::Interface * parent = nullptr) override {
            if (_count < loggerCount) {
              auto context = new(&(_contexts[_count])) Context(label, parent);
              auto logger = new(&(_loggers[_count])) Logger(context, _transportList, this);
              _count++;
              return logger;
            }
            return nullptr;
          }

          const Level::Level getLevel() const override {
            return _level;
          }

        private:

          using Logger = Logger::Instance<messageSize, transportCount>;
          using Context = Context::Instance<transportCount>;

          const Level::Level _level;
          char _loggers[loggerCount][sizeof(Logger)];
          char _contexts[loggerCount][sizeof(Context)];
          const TransportList _transportList;
          size_t _count;

      };

    }
  }
}
