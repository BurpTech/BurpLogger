#include "Level.hpp"

namespace BurpLogger {
  namespace Internal {
    namespace Level {

      #define C_STR_CASE(LEVEL) case LEVEL: return #LEVEL
      #define C_STR_DEFAULT default: return "unknown"
      const char * c_str(const Level level) {
        switch (level) {
          C_STR_CASE(error);
          C_STR_CASE(warn);
          C_STR_CASE(info);
          C_STR_CASE(verbose);
          C_STR_CASE(debug);
          C_STR_CASE(silly);
          C_STR_DEFAULT;
        }
      }

    }
  }
}
