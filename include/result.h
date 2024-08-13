/// A simple Result type for C inspired by Rust's Result type.
/// Should work with any C version but only tested with C23.
///
/// Example:
///
/// ```c
/// #include <stdio.h> // fprintf
/// #include <stdlib.h> // exit
/// #include <result.h> // this file
///
/// Implment the fail function that is called when unwrap fails.
/// [[noreturn]]
/// void _result_fail(const char *file, int line) {
///   fprintf(stderr, "Unwrap failed at %s:%d\n", file, line);
///   exit(1);
/// }
///
/// // Declare the Result type.
/// RESULT_DECL(int, int);
///
/// // use the Result type.
/// Result(int, int) divide(int a, int b) {
///  if (b == 0) {
///  	return Err(int, int, -1);
///  }
///  return Ok(int, int, a / b);
///  }
///
/// int main() {
///  	Result(int, int) result = divide(10, 2);
///
///  	if_let_ok(result, value) {
///  		printf("Result: %d\n", value);
///  	} else {
///  		printf("Division failed and I don't know why\n");
///  	}
/// }
///
/// ```

#ifndef RESULT_H
#define RESULT_H

#ifndef RESULT_FAIL
#define RESULT_FAIL _result_fail
[[noreturn]] void _result_fail(const char *file, int line);
#endif

#define RESULT_UNIQ_CAT(n) uniq_##n
#define RESULT_UNIQ_(n) RESULT_UNIQ_CAT(n)
#define RESULT_UNIQ() RESULT_UNIQ_(__LINE__)

#define RESULT_T(V, E) result_##V##_##E##_t
#define Result(V, E) RESULT_T(V, E)

#define RESULT_DECL(V, E)                                                      \
  typedef struct {                                                             \
    bool is_ok;                                                                \
    union {                                                                    \
      V ok;                                                                    \
      E err;                                                                   \
    };                                                                         \
  } Result(V, E);

#define Ok(V, E, v)                                                            \
  (Result(V, E)) { .is_ok = true, .ok = v }

#define Err(V, E, e)                                                           \
  (Result(V, E)) { .is_ok = false, .err = e }

#define unwrap(result)                                                         \
  ((result.is_ok ? (void)0 : RESULT_FAIL(__FILE__, __LINE__)), result.ok)

#define unwrap_or(result, or) (result.is_ok ? result.ok : or)

#define if_let_ok(result, name)                                                \
  for (bool __##name##_once = true; __##name##_once; __##name##_once = false)  \
    for (auto name##_result = result; __##name##_once;                         \
         __##name##_once = false)                                              \
      if (name##_result.is_ok)                                                 \
        for (auto name = name##_result.ok; __##name##_once;                    \
             __##name##_once = false)

#endif // !RESULT_H
