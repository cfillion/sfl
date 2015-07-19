#ifndef SFL_ERRORS_HPP
#define SFL_ERRORS_HPP

#include "macros.hpp"

#define ERROR_TYPE(type) class SFL_EXPORT type : public error {};

namespace sfl {
  class SFL_EXPORT error {};

  ERROR_TYPE(duplicate_definition);
  ERROR_TYPE(illegal_name);
  ERROR_TYPE(invalid_assignment);
  ERROR_TYPE(invalid_conversion);
  ERROR_TYPE(missing_doctor);
  ERROR_TYPE(missing_registry);
  ERROR_TYPE(undefined_value);
  ERROR_TYPE(unknown_object);

  // new paragraph to sort the error types easily
};

#undef ERROR_TYPE

#endif
