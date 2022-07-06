#ifndef __MERGER_LUA_API_FINDFILE_H__
#define __MERGER_LUA_API_FINDFILE_H__

#include "lua_api.h"

#define MERGER_LUA_API_FINDFILE(XX) \
XX(\
"findfile", merger_lua_api_findfile, "Searches a directory for a file",                 \
"SYNOPSIS"                                                                          CRLF\
"    list findfile(path);"                                                          CRLF\
                                                                                    CRLF\
"DESCRIPTION"                                                                       CRLF\
"    The findfile() function searches a directory for a file or subdirectory"       CRLF\
"    with a name that matches a specific name (or partial name if wildcards are"    CRLF\
"    used)."                                                                        CRLF\
                                                                                    CRLF\
"    The `path` means a directory or path, and the file name. The file name can"    CRLF\
"    include wildcard characters, for example, an asterisk (*) or a question"       CRLF\
"    mark (?)."                                                                     CRLF\
                                                                                    CRLF\
"    The return list has been reorder by alphabetical order."                       CRLF\
)

#ifdef __cplusplus
extern "C" {
#endif

int merger_lua_api_findfile(lua_State* L);

#ifdef __cplusplus
}
#endif
#endif
