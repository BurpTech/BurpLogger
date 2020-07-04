#pragma once

#include <array>
#include <cstddef>
namespace BurpLogger {
  namespace Internal {

    class Context {

      public:

        Context(const char * label, const Context * parent = nullptr);
        const char * getLabel() const;
        const Context * getParent() const;

      private:

        const char * _label;
        const Context * _parent;

    };

  }
}
