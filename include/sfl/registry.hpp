#ifndef SFL_REGISTRY_HPP
#define SFL_REGISTRY_HPP

#include <string>
#include <unordered_map>

#include "macros.hpp"

namespace sfl {
  class SFL_EXPORT definition {
  public:
    definition(const std::string &name, const int user_data = -1);

    const std::string &name() const { return m_name; }
    int user_data() const { return m_user_data; }

  private:
    std::string m_name;
    int m_user_data;
  };

  typedef std::unordered_map<std::string, definition> definition_map;

  class SFL_EXPORT registry {
  public:
    registry() {}

    const definition &at(const std::string &k) const
    { return m_definitions.at(k); }
    int count(const std::string &k) const { return m_definitions.count(k); }

    void add(const definition &d);

  private:
    definition_map m_definitions;
  };
};

#endif
