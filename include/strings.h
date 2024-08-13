#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include <string.h>

typedef struct {
  char *data;
  uint32_t length;
  uint32_t capacity; // 0 if not owned
} string_t;

#define string_const(str)                                                      \
  { str, sizeof(str) - 1, 0 }

#define string_owned(str)                                                      \
  { str, sizeof(str) - 1, sizeof(str) - 1 }

#define string_view(str)                                                       \
  { str, strlen(str), 0 }

#define string_dup(s) string_with_capacity(s.length)

#define strf(s) s.length, s.data

#define stre(s) s.data, s.length

string_t string_with_capacity(uint32_t capacity);

#endif // STRING_H
