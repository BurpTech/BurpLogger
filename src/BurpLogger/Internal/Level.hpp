#pragma once

namespace BurpLogger {
  namespace Internal {
    namespace Level {

      enum Level {
        error,
        warn,
        info,
        verbose,
        debug,
        silly
      };

      const char * c_str(const Level level);

    }
  }
}
