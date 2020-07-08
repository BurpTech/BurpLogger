#pragma once

namespace BurpLogger {
  namespace Internal {
    namespace Level {

      enum Level {
        none = 0,
        always = 0,
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
