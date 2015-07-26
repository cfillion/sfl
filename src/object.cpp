#include <sfl/object.hpp>

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/format.hpp>
#include <sfl/doctor.hpp>
#include <sfl/errors.hpp>

using namespace boost;
using namespace sfl;
using namespace std;

object::object(const string &name, const sfl::location &loc)
  : m_location(loc)
{
  const registry *reg = location().registry();

  if(!reg)
    throw missing_registry();

  const string lc_name = to_lower_copy(name);

  if(!reg->count(lc_name)) {
    error_at(location(), format("unknown object name '%s'") % name);
    throw unknown_object();
  }

  m_definition = &reg->at(lc_name);
}

int object::var_count(const std::string &name) const
{
  // TODO: count up in the object tree
  return m_definition->properties().count(name) + m_variables.count(name);
}

void object::var_set(const variable &var)
{
  if(var.is_property() && !m_definition->properties().count(var.name()))
    throw unknown_property();

  m_variables.erase(var.name());
  m_variables.insert({var.name(), var});
}

const variable &object::var_get(const std::string &name) const
{
  if(m_variables.count(name))
    return m_variables.at(name);
  else if(m_definition->properties().count(name))
    return m_definition->properties().at(name);
  else
    throw undefined_variable();
}
