#ifndef SFL_ERRORS_HPP
#define SFL_ERRORS_HPP

#include "macros.hpp"

#include <exception>

#define ERROR_TYPE(type) class SFL_EXPORT type : public error { \
  const char *what() const noexcept override { return "sfl::"#type; } \
};

namespace sfl {
  class SFL_EXPORT error : public std::exception {
    const char *what() const noexcept override = 0;
  };

  ERROR_TYPE(duplicate_definition);
  ERROR_TYPE(duplicate_property);
  ERROR_TYPE(illegal_name);
  ERROR_TYPE(invalid_assignment);
  ERROR_TYPE(invalid_conversion);
  ERROR_TYPE(missing_doctor);
  ERROR_TYPE(missing_registry);
  ERROR_TYPE(undefined_value);
  ERROR_TYPE(undefined_variable);
  ERROR_TYPE(unknown_object);
  ERROR_TYPE(unknown_property);

  // new paragraph to sort the error types easily
};

#undef ERROR_TYPE

#endif
