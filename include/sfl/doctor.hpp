#ifndef SFL_DOCTOR_HPP
#define SFL_DOCTOR_HPP

#include <boost/format/format_fwd.hpp>
#include <vector>

#include "diagnosis.hpp"
#include "macros.hpp"

namespace sfl {
  typedef std::vector<diagnosis> diagnosis_bag;

  SFL_EXPORT void error_at(const location &, const boost::format &);
  SFL_EXPORT void error_at(const location &, const std::string &);

  SFL_EXPORT void diagnose_at(const location &,
    const std::string &, const enum diagnosis::level);

  class SFL_EXPORT doctor {
  public:
    const std::vector<diagnosis> &bag() const { return m_bag; }

    void add_diagnosis(const std::string &, const enum diagnosis::level,
      const location & = location());
    void add_diagnosis(const diagnosis &dia);

    bool empty() const { return m_bag.empty(); }

  private:
    diagnosis_bag m_bag;
  };
};

#endif
