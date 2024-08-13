#ifndef FS_H
#define FS_H

#include <result.h>
#include <strings.h>
RESULT_DECL(string_t, string_t);

typedef Result(string_t, string_t) file_read_result_t;

file_read_result_t read_file_to_string(string_t path);

#endif // FS_H
