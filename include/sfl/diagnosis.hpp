#ifndef SFL_DIAGNOSIS_HPP
#define SFL_DIAGNOSIS_HPP

#include <ostream>

#include "location.hpp"
#include "macros.hpp"

namespace sfl {
  class SFL_EXPORT diagnosis {
  public:
    enum level { error, warning, note };

    diagnosis(const level lvl, const std::string &msg,
      const location &loc = sfl::location())
      : m_level(lvl), m_message(msg), m_location(loc) {}

    enum level level() const { return m_level; }
    const std::string &message() const { return m_message; }
    const class location &location() const { return m_location; }

  private:
    enum level m_level;
    std::string m_message;
    sfl::location m_location;
  };

  SFL_EXPORT bool operator==(const diagnosis &left, const diagnosis &right);
  SFL_EXPORT bool operator!=(const diagnosis &left, const diagnosis &right);
  SFL_EXPORT std::ostream &operator<<(std::ostream &os, const diagnosis &value);
};

#endif
