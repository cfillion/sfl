#include <sfl/variable.hpp>

using namespace sfl;

variable::variable(const std::string &name, const variable::type t,
    const class location &loc)
  : m_name(name), m_type(type_of(t)), m_location(loc), m_undefined(true)
{}

variable::variable(const std::string &name, const value_variant &v,
    const class location &loc)
  : m_name(name), m_value(v), m_type(m_value.type()), m_location(loc), m_undefined(false)
{}

std::type_index variable::type_of(const type t) const
{
  switch(t) {
  case string:
    return typeid(std::string);
  }
}
