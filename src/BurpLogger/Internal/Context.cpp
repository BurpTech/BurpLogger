#include "Context.hpp"

namespace BurpLogger {
  namespace Internal {

    Context::Context(const char * label, const Context * parent) :
      _label(label),
      _parent(parent)
    {}

    const char * Context::getLabel() const {
      return _label;
      }

    const Context * Context::getParent() const {
      return _parent;
    }

  }
}
