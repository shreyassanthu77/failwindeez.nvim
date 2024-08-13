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
  ((string_t){.data = str, .length = sizeof(str) - 1, .capacity = 0})

#define string_constn(str, len)                                                \
  ((string_t){.data = str, .length = len, .capacity = 0})

#define string_owned(str)                                                      \
        ((string_t){.data = str, .length = strlen(str), .capacity = strlen(str) + 1}

#define string_ownedn(str, len)                                                \
                        ((string_t){.data = str, .length = len, .capacity = len + 1}

#define string_view(str)                                                       \
  ((string_t){.data = str, .length = strlen(str), .capacity = 0})

#define string_viewn(str, len)                                                 \
  ((string_t){.data = str, .length = len, .capacity = 0})

#define string_dup(s) string_with_capacity(s.length)

#define strf(s) s.length, s.data

#define stre(s) s.data, s.length

string_t string_with_capacity(uint32_t capacity);

#endif // STRING_H
