#pragma once

#include <cstddef>
#include <cstring>
#include "../src/BurpLogger.hpp"

template <size_t messageSize>
class TestTransport : public BurpLogger::Transport {

  public:

    char message[messageSize];

    void log(const BurpLogger::Entry & entry) override {
      strncpy(message, "", messageSize);
      char temp[messageSize];
      const BurpLogger::Labels * labels = entry.getLabels();
      while (labels) {
        if (strlen(message) == 0) {
          strncpy(message, labels->getLabel(), messageSize);
        } else {
          strncpy(temp, message, messageSize);
          snprintf(message, messageSize, "%s: %s", labels->getLabel(), temp);
        }
        labels = labels->getParent();
      }
      strncpy(temp, message, messageSize);
      snprintf(
          message,
          messageSize,
          "%s: %s: %s",
          temp,
          BurpLogger::Level::c_str(entry.getLevel()),
          entry.getMessage()
      );
    }

};
