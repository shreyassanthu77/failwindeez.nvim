#ifndef STRING_H
#define STRING_H
#include <stdint.h>

typedef struct {
  char *data;
  uint32_t length;
} string_t;

#define string_const(str)                                                      \
  { str, sizeof(str) - 1 }

#define strf(s) s.length, s.data

#define stre(s) s.data, s.length

#endif // STRING_H
