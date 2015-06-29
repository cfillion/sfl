#if defined _WIN32 || defined __CYGWIN__
  #ifdef SFL_SHARED
    #define SFL_EXPORT __declspec(dllexport)
  #else
    #define SFL_EXPORT __declspec(dllimport)
  #endif

  #define SFL_PRIVATE
#endif

#define SFL_EXPORT __attribute__((visibility("default")))
#define SFL_PRIVATE __attribute__((visibility("hidden")))
