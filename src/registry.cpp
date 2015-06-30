#include <boost/algorithm/string/case_conv.hpp>
#include <regex>
#include <sfl/errors.hpp>
#include <sfl/registry.hpp>

using namespace sfl;
using namespace std;

static const regex NAME_REGEX("^[a-z_][a-z0-9_]*$");

definition::definition(const string &name, const int user_data)
  : m_name(name), m_user_data(user_data)
{
  boost::to_lower(m_name);

  smatch matches;
  regex_match(m_name, matches, NAME_REGEX);

  if(matches.empty())
    throw illegal_name();
}

void registry::add(const definition &def)
{
  if(count(def.name()))
    throw duplicate_definition();

  m_definitions.insert({def.name(), def});
}
