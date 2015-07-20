#ifndef SFL_VARIABLE_HPP
#define SFL_VARIABLE_HPP

#include "errors.hpp"
#include "location.hpp"
#include "macros.hpp"

#include <boost/variant.hpp>
#include <string>
#include <typeindex>

namespace sfl {
  typedef boost::variant<std::string, int> value_variant;

  class SFL_EXPORT variable {
  public:
    enum type {
      string,
    };

    variable(const std::string &name, const enum type t,
      const class location &loc = sfl::location());
    variable(const std::string &name, const value_variant &v,
      const class location &loc = sfl::location());

    const std::string &name() const { return m_name; }
    const class location &location() const { return m_location; }
    bool empty() const { return m_undefined; }

    template<typename T>
    variable &operator=(const T &val)
    {
      // creating a temporary variant allows the assignment of compatible
      // but not strictly equal types (eg. a const char * in a string variable)
      const value_variant test = val;
      if(std::type_index(test.type()) != m_type)
        throw invalid_assignment();

      m_value = val;
      m_undefined = false;
      return *this;
    }

    template<typename T>
    const T &get() const
    {
      if(std::type_index(typeid(T)) != m_type)
        throw invalid_conversion();
      else if(m_undefined)
        throw undefined_value();

      return boost::get<T>(m_value);
    }

  private:
    std::type_index type_of(const type) const;

    std::string m_name;
    value_variant m_value;
    std::type_index m_type;
    class location m_location;
    bool m_undefined;
  };
};

#endif
