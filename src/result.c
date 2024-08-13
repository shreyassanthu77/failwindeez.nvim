#include <result.h>
#include <stdio.h>
#include <stdlib.h>

[[noreturn]]
void _result_fail(const char *file, int line) {
  fprintf(stderr, "Unwrap failed at %s:%d\n", file, line);
  exit(1);
}
