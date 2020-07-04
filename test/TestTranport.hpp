#pragma once

#include <cstddef>
#include <cstring>
#include <stdarg.h>
#include "../src/BurpLogger.hpp"

template <size_t messageSize>
class TestTransport : public BurpLogger::Transport {

  public:

    void log(const BurpLogger::Context & context, const BurpLogger::Entry & entry) override {
      _init(context.getLabel());
      const BurpLogger::Context * parent = context.getParent();
      while (parent) {
        _printf("%s: %s", parent->getLabel(), getMessage());
        parent = parent->getParent();
      }
      _printf(
          "%s: %s: %s",
          BurpLogger::Level::c_str(entry.getLevel()),
          getMessage(),
          entry.getMessage()
      );
    }

    const char * getMessage() {
      return _buffers[_current];
    }

  private:

    char _buffers[2][messageSize];
    unsigned char _current = 0;

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
