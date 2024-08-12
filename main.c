#include <stdio.h>
#include <string.h>
#include <tree-sitter-css.h>
#include <tree_sitter/api.h>

int main() {
  const string_t src = string_const("body {\n"
                                    "  color: red;\n"
                                    "}\n");

  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_css());

  TSTree *tree = ts_parser_parse_string(parser, NULL, stre(src));

  TSNode root = ts_tree_root_node(tree);
  printf("root: %s\n", ts_node_string(root));
  return 0;
}
