#include <fs.h>
#include <stdio.h>
#include <strings.h>

Result(string_t, string_t) read_file_to_string(string_t path) {
  FILE *f = fopen(path.data, "r");
  if (!f) {
    return Err(string_t, string_t, string_const("file not found"));
  }
  fseek(f, 0, SEEK_END);
  size_t size = ftell(f);
  fseek(f, 0, SEEK_SET);
  string_t result = string_with_capacity(size);
  size_t read = fread(result.data, 1, size, f);
  if (read != size) {
    fclose(f);
    return Err(string_t, string_t, string_const("read error"));
  }
  fclose(f);
  result.length = size;
  return Ok(string_t, string_t, result);
}
