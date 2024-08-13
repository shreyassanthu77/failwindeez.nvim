#include <stdlib.h>
#include <strings.h>

string_t string_with_capacity(uint32_t capacity) {
  char *data = calloc(capacity, sizeof(char));
  if (!data) {
    return (string_t){0};
  }
  return (string_t){
      .data = data,
      .length = 0,
      .capacity = capacity,
  };
}
