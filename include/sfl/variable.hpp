#ifndef SFL_VARIABLE_HPP
#define SFL_VARIABLE_HPP

#include "errors.hpp"
#include "location.hpp"
#include "macros.hpp"

#include <boost/variant.hpp>
#include <string>
#include <unordered_map>

namespace sfl {
  typedef boost::variant<std::string, int> value_variant;

  class SFL_EXPORT variable {
  public:
    enum type {
      string,
      temp_type, // TODO: replace me
    };

    variable(const std::string &name, const enum type t,
      const class location &loc = sfl::location());
    variable(const std::string &name, const value_variant &v,
      const class location &loc = sfl::location());

    const std::string &name() const { return m_name; }
    enum type type() const { return m_type; }
    const class location &location() const { return m_location; }
    bool empty() const { return m_undefined; }
    bool is_property() const;

    template<typename T>
    variable &operator=(const T &val)
    {
      // creating a temporary variant allows the assignment of compatible
      // but not strictly equal types (eg. a const char * in a string variable)
      const value_variant test{val};
      if(test.which() != m_type)
        throw invalid_assignment();

      m_value = val;
      m_undefined = false;
      return *this;
    }

    template<typename T>
    const T &get() const
    {
      if(m_undefined)
        throw undefined_value();

      try {
        return boost::get<T>(m_value);
      }
      catch(const boost::bad_get &) {
        throw invalid_conversion();
      }
    }

  private:
    std::string m_name;
    value_variant m_value;
    enum type m_type;
    class location m_location;
    bool m_undefined;

    friend bool operator==(const variable &, const variable &);
  };

  typedef std::unordered_map<std::string, variable> variable_map;

  SFL_EXPORT bool operator==(const variable &, const variable &);
  SFL_EXPORT bool operator!=(const variable &, const variable &);
};

#endif
