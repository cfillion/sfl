#ifndef SFL_OBJECT_HPP
#define SFL_OBJECT_HPP

#include <string>

#include "location.hpp"
#include "registry.hpp"
#include "variable.hpp"
#include "macros.hpp"

namespace sfl {
  class SFL_EXPORT object {
  public:
    object(const std::string &name, const location &loc);

    int user_data() const { return m_definition->user_data(); }
    const std::string &name() const { return m_definition->name(); }
    const class location &location() const { return m_location; }

    int var_count(const std::string &) const;
    void var_set(const variable &);
    const variable &var_get(const std::string &) const;
    template<typename T>
    const T &var_value(const std::string &name) const
    {
      return var_get(name).get<T>();
    }

  private:
    const sfl::definition *m_definition;
    sfl::location m_location;
    variable_map m_variables;
  };
};

#endif
