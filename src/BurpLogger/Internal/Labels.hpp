#pragma once

#include <array>
#include <cstddef>
namespace BurpLogger {
  namespace Internal {

    class Labels {

      public:

        Labels(const char * label, const Labels * parent = nullptr);
        const char * getLabel() const;
        const Labels * getParent() const;

      private:

        const char * _label;
        const Labels * _parent;

    };

  }
}
