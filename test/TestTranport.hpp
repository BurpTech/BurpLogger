#pragma once

#include <cstddef>
#include <cstring>
#include <stdarg.h>
#include "../src/BurpLogger.hpp"

template <size_t messageSize, size_t loggerCount>
class TestTransport : public BurpLogger::Transport::Interface {

  public:

    const void * cache(const BurpLogger::Context * context) override {
      if (_contextCount < loggerCount) {
        char * contextString = _contextStrings[_contextCount++];
        _init(context->getLabel());
        const BurpLogger::Context * parent = context->getParent();
        while (parent) {
          _printf("%s: %s", parent->getLabel(), getMessage());
          parent = parent->getParent();
        }
        strncpy(contextString, getMessage(), messageSize);
        return contextString;
      }
      return nullptr;
    }

    void log(const void * cache, const BurpLogger::Entry & entry) override {
      const char * contextString = static_cast<const char *>(cache);
      _printf(
          "%s: %s: %s",
          BurpLogger::Level::c_str(entry.getLevel()),
          contextString,
          entry.getMessage()
      );
    }

    const char * getMessage() {
      return _buffers[_current];
    }

    void reset() {
      _init("");
    }

  private:

    char _buffers[2][messageSize];
    unsigned char _current = 0;
    char _contextStrings[loggerCount][messageSize];
    size_t _contextCount = 0;

    void _init(const char * source) {
      strncpy(_buffers[_current], source, messageSize);
    }

    void _printf(const char * format, ...) {
      _current = (_current + 1) % 2;
      va_list args;
      va_start(args, format);
      vsnprintf(_buffers[_current], messageSize, format, args);
      va_end(args);
    }

};
