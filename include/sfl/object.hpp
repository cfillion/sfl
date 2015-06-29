#ifndef SFL_OBJECT_HPP
#define SFL_OBJECT_HPP

#include <string>

#include "location.hpp"
#include "registry.hpp"
#include "macros.hpp"

namespace sfl {
  class definition;

  class SFL_EXPORT object {
  public:
    object(const std::string &name, const location &loc);

    int user_data() const { return m_definition->user_data(); }
    const std::string &name() const { return m_definition->name(); }

    const location &location() const { return m_location; }

  private:
    const sfl::definition *m_definition;
    sfl::location m_location;
  };
};

#endif
