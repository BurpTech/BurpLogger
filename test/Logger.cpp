#include <cstddef>
#include <cstdio>
#include <unity.h>
#include "../src/BurpLogger.hpp"
#include "TestTranport.hpp"
#include "Logger.hpp"

#define LEVEL_TEST(LEVEL)\
  d.describe(#LEVEL, [](Describe & d) {\
      d.it("should log the message with level " #LEVEL, []() {\
          logger->LEVEL("message: %d: %d", 1, 2);\
          TEST_ASSERT_EQUAL_STRING(#LEVEL ": label1: label2: label3: message: 1: 2", transport.getMessage());\
      });\
  })

namespace Logger {

  constexpr size_t messageSize = 256;
  constexpr size_t transportCount = 1;
  constexpr size_t loggerCount = 3;
    
  using namespace BurpLogger;
  using Factory = BurpLogger::Factory<messageSize, transportCount, loggerCount>;

  TestTransport<messageSize, loggerCount> transport;
  const Factory::Transports transports = {
    &transport
  };
  Factory factory(transports);
  auto parent1 = factory.create("label1");
  auto parent2 = parent1->create("label2");
  auto logger = parent2->create("label3");

  Module tests("Logger", [](Describe & d) {

      d.describe("log", [](Describe & d) {
          d.it("should log the message with the level", []() {
              logger->log(Level::info, "message: %d: %d", 1, 2);
              TEST_ASSERT_EQUAL_STRING("info: label1: label2: label3: message: 1: 2", transport.getMessage());
          });
      });

      LEVEL_TEST(error);
      LEVEL_TEST(warn);
      LEVEL_TEST(info);
      LEVEL_TEST(verbose);
      LEVEL_TEST(debug);
      LEVEL_TEST(silly);

  });

}
