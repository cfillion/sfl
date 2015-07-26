#include <sfl/variable.hpp>

using namespace sfl;

variable::variable(const std::string &name, const enum type t,
    const class location &loc)
  : m_name(name), m_type(t), m_location(loc), m_undefined(true)
{}

variable::variable(const std::string &name, const value_variant &v,
    const class location &loc)
  : m_name(name), m_value(v), m_type(static_cast<enum type>(m_value.which())),
    m_location(loc), m_undefined(false)
{}

bool variable::is_property() const
{
  return m_name[0] == '@';
}

bool sfl::operator==(const variable &left, const variable &right)
{
  return left.name() == right.name() &&
    left.type() == right.type() &&
    left.m_value == right.m_value &&
    left.location() == right.location();
}

bool sfl::operator!=(const variable &left, const variable &right)
{
  return !(left == right);
}
