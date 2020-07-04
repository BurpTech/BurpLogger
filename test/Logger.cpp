#include <cstddef>
#include <cstdio>
#include <unity.h>
#include "../src/BurpLogger.hpp"
#include "TestTranport.hpp"
#include "Logger.hpp"

#define LEVEL_TEST(LEVEL)\
  d.describe(#LEVEL, [](Describe & d) {\
      d.it("should log the message with level " #LEVEL, []() {\
          logger.LEVEL("message: %d: %d", 1, 2);\
          TEST_ASSERT_EQUAL_STRING("label1: label2: label3: " #LEVEL ": message: 1: 2", transport.message);\
      });\
  })

namespace Logger {

  constexpr size_t messageSize = 256;
    
  using namespace BurpLogger;
  using Logger = BurpLogger::Logger<messageSize>;
  using TransportList = BurpLogger::TransportList<1>;

  TestTransport<messageSize> transport;
  const TransportList::Transports transports = {
    &transport
  };
  const TransportList transportList(transports);
  Logger parent1("label1", transportList);
  Logger parent2("label2", parent1);
  Logger logger("label3", parent2);

  Module tests("Logger", [](Describe & d) {

      d.describe("log", [](Describe & d) {
          d.it("should log the message with the level", []() {
              logger.log(Level::info, "message: %d: %d", 1, 2);
              TEST_ASSERT_EQUAL_STRING("label1: label2: label3: info: message: 1: 2", transport.message);
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
