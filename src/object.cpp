#include <boost/algorithm/string/case_conv.hpp>
#include <boost/format.hpp>
#include <sfl/doctor.hpp>
#include <sfl/errors.hpp>
#include <sfl/object.hpp>

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
