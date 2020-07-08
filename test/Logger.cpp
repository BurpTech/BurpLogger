#include <cstddef>
#include <cstdio>
#include <unity.h>
#include "../src/BurpLogger.hpp"
#include "TestTranport.hpp"
#include "Logger.hpp"

#define SHOULD_LOG(LOGGER, LEVEL)\
  d.describe(#LEVEL, [](Describe & d) {\
      d.it("should log the message with level " #LEVEL, []() {\
          LOGGER##Logger->LEVEL("message: %d: %d", 1, 2);\
          TEST_ASSERT_EQUAL_STRING(#LEVEL ": label1: label2: label3: message: 1: 2", transport.getMessage());\
      });\
  })

#define SHOULD_NOT_LOG(LOGGER, LEVEL)\
  d.describe(#LEVEL, [](Describe & d) {\
      d.it("should not log the message with level " #LEVEL, []() {\
          LOGGER##Logger->LEVEL("message: %d: %d", 1, 2);\
          TEST_ASSERT_EQUAL_STRING("", transport.getMessage());\
      });\
  })

namespace Logger {

  constexpr size_t messageSize = 256;
  constexpr size_t transportCount = 1;
  constexpr size_t loggerCount = 3;
    
  using namespace BurpLogger;
  using Factory = BurpLogger::Factory<messageSize, transportCount, loggerCount>;

  TestTransport<messageSize, loggerCount * 3> transport;
  const Factory::Transports transports = {
    &transport
  };

  Factory sillyFactory(Level::silly, transports);
  auto sillyParent1 = sillyFactory.create("label1");
  auto sillyParent2 = sillyParent1->create("label2");
  auto sillyLogger = sillyParent2->create("label3");

  Factory infoFactory(Level::info, transports);
  auto infoParent1 = infoFactory.create("label1");
  auto infoParent2 = infoParent1->create("label2");
  auto infoLogger = infoParent2->create("label3");

  Factory noneFactory(Level::none, transports);
  auto noneParent1 = noneFactory.create("label1");
  auto noneParent2 = noneParent1->create("label2");
  auto noneLogger = noneParent2->create("label3");

  BurpStatus::Status status;

  Module tests("Logger", [](Describe & d) {

      d.beforeEach([]() {
          transport.reset();
      });

      d.describe("log", [](Describe & d) {
          d.it("should log the message with the level", []() {
              sillyLogger->log(Level::info, "message: %d: %d", 1, 2);
              TEST_ASSERT_EQUAL_STRING("info: label1: label2: label3: message: 1: 2", transport.getMessage());
          });
          d.describe("with status level INFO", [](Describe & d) {
            d.it("should log the status string as info", []() {
                status.set(BurpStatus::Status::Level::INFO, BurpStatus::Status::ok);
                sillyLogger->log("label", status);
                TEST_ASSERT_EQUAL_STRING("info: label1: label2: label3: label: BurpStatus::Status : ok", transport.getMessage());
            });
          });
          d.describe("with status level WARNING", [](Describe & d) {
            d.it("should log the status string as warn", []() {
                status.set(BurpStatus::Status::Level::WARNING, BurpStatus::Status::ok);
                sillyLogger->log("label", status);
                TEST_ASSERT_EQUAL_STRING("warn: label1: label2: label3: label: BurpStatus::Status : ok", transport.getMessage());
            });
          });
          d.describe("with status level ERROR", [](Describe & d) {
            d.it("should log the status string as error", []() {
                status.set(BurpStatus::Status::Level::ERROR, BurpStatus::Status::ok);
                sillyLogger->log("label", status);
                TEST_ASSERT_EQUAL_STRING("error: label1: label2: label3: label: BurpStatus::Status : ok", transport.getMessage());
            });
          });
      });

      d.describe("with the log level set to silly", [](Describe & d) {
          SHOULD_LOG(silly, always);
          SHOULD_LOG(silly, error);
          SHOULD_LOG(silly, warn);
          SHOULD_LOG(silly, info);
          SHOULD_LOG(silly, verbose);
          SHOULD_LOG(silly, debug);
          SHOULD_LOG(silly, silly);
      });

      d.describe("with the log level set to info", [](Describe & d) {
          SHOULD_LOG(info, always);
          SHOULD_LOG(info, error);
          SHOULD_LOG(info, warn);
          SHOULD_LOG(info, info);
          SHOULD_NOT_LOG(info, verbose);
          SHOULD_NOT_LOG(info, debug);
          SHOULD_NOT_LOG(info, silly);
      });

      d.describe("with the log level set to none", [](Describe & d) {
          SHOULD_LOG(none, always);
          SHOULD_NOT_LOG(none, error);
          SHOULD_NOT_LOG(none, warn);
          SHOULD_NOT_LOG(none, info);
          SHOULD_NOT_LOG(none, verbose);
          SHOULD_NOT_LOG(none, debug);
          SHOULD_NOT_LOG(none, silly);
      });

  });

}
