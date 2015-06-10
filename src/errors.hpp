#ifndef SFL_ERRORS_HPP
#define SFL_ERRORS_HPP

#define ERROR_TYPE(type) class type : public error {};

namespace sfl {
  class error : public std::exception {};

  ERROR_TYPE(unknown_object_error);
};

#undef ERROR_TYPE

#endif