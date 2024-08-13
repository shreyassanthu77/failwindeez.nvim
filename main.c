#include <assert.h>
#include <fs.h>
#include <result.h>
#include <stdarg.h>
#include <stdio.h>
#include <strings.h>
#include <tree-sitter-css.h>
#include <tree_sitter/api.h>

[[noreturn]]
void panic(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  exit(1);
}

string_t node_value(TSNode node, string_t src) {
  uint32_t start_byte = ts_node_start_byte(node);
  uint32_t end_byte = ts_node_end_byte(node);
  return string_viewn(src.data + start_byte, end_byte - start_byte);
}

const string_t options_query_str =
    string_const("((rule_set"
                 "(selectors (tag_name) @tag)"
                 "(block"
                 "  (declaration (property_name) @option (_) @value )))"
                 "(#eq? @tag \"options\"))");

int generate_config(string_t src) {
  TSParser *parser = ts_parser_new();
  TSLanguage const *lang = tree_sitter_css();
  ts_parser_set_language(parser, lang);

  TSTree *tree = ts_parser_parse_string(parser, NULL, stre(src));
  TSNode root = ts_tree_root_node(tree);

  uint32_t error_offset = 0;
  TSQueryError error = {0};
  TSQuery *options_query =
      ts_query_new(lang, stre(options_query_str), &error_offset, &error);

  if (options_query == NULL) {
    // Handle error
    panic("Parsing options query failed type: %d, offset: %d\n", error,
          error_offset);
  }

  TSQueryCursor *cursor = ts_query_cursor_new();
  ts_query_cursor_exec(cursor, options_query, root);

  TSQueryMatch match;
  while (ts_query_cursor_next_match(cursor, &match)) {
    assert(match.capture_count == 3);
    string_t name = node_value(match.captures[1].node, src);
    string_t value = node_value(match.captures[2].node, src);
    printf("%.*s: %.*s\n", strf(name), strf(value));
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }
  string_t file_name = string_view(argv[1]);

  if_let_ok(read_file_to_string(file_name), src) {
    return generate_config(src);
  }
  else {
    printf("%.*s\n", strf(src_result.err));
  }
  return 0;
}
