#ifndef SFL_LOCATION_HPP
#define SFL_LOCATION_HPP

#include <boost/format/format_fwd.hpp>

#include "macros.hpp"

namespace sfl {
  class doctor;
  class registry;

  struct context {
    sfl::doctor *doctor;
    sfl::registry *registry;
  };

  class SFL_EXPORT location {
  public:
    location(const context &c = sfl::context());

    class doctor *doctor() const { return m_context.doctor; }
    class registry *registry() const { return m_context.registry; }

  private:
    const struct context &context() const { return m_context; }
    sfl::context m_context;

    friend bool operator==(const location &, const location &);
  };

  SFL_EXPORT bool operator==(const context &, const context &);
  SFL_EXPORT bool operator!=(const context &, const context &);

  SFL_EXPORT bool operator==(const location &, const location &);
  SFL_EXPORT bool operator!=(const location &, const location &);
};

#endif
