#include <sfl/variable.hpp>

using namespace sfl;

variable::variable(const std::string &name, const enum type t,
    const class location &loc)
  : m_name(name), m_type(type_of(t)), m_type_id(t),
    m_location(loc), m_undefined(true)
{}

variable::variable(const std::string &name, const value_variant &v,
    const class location &loc)
  : m_name(name), m_value(v), m_type(m_value.type()),
    m_type_id(static_cast<enum type>(m_value.which())),
    m_location(loc), m_undefined(false)
{}

std::type_index variable::type_of(const enum type t) const
{
  switch(t) {
  case string:
    return typeid(std::string);
  }
}
