#include <fs.h>
#include <result.h>
#include <stdio.h>
#include <strings.h>

const char *options_query =
    "((rule_set"
    "(selectors (tag_name) @tag)"
    "(block"
    "  (declaration (property_name) @option (_) @value )))"
    "(#eq? @tag \"options\"))";

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }
  string_t file_name = string_view(argv[1]);

  if_let_ok(read_file_to_string(file_name), src) {
    printf("File contents: %.*s\n", (int)src.length, src.data);
  }
  else {
    printf("%.*s\n", strf(src_result.err));
  }
  return 0;
}
