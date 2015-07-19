#include <sfl/variable.hpp>

using namespace sfl;

variable::variable(const std::string &name, const variable::type type,
    const class location &loc)
  : m_name(name), m_type(type_of(type)), m_location(loc), m_undefined(true)
{
}

std::type_index variable::type_of(const type t) const
{
  switch(t) {
  case string:
    return typeid(std::string);
  }
}
