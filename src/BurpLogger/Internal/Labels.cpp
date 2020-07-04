#include "Labels.hpp"

namespace BurpLogger {
  namespace Internal {

    Labels::Labels(const char * label, const Labels * parent) :
      _label(label),
      _parent(parent)
    {}

    const char * Labels::getLabel() const {
      return _label;
    }

    const Labels * Labels::getParent() const {
      return _parent;
    }

  }
}
