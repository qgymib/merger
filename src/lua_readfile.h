#ifndef __MERGER_LUA_API_READFILE_H__
#define __MERGER_LUA_API_READFILE_H__

#include "lua_api.h"

#define MERGER_LUA_API_READFILE(XX) \
XX(                                                                                     \
"readfile", merger_lua_api_readfile, "Read the whole file content and return.",         \
"SYNOPSIS"                                                                          CRLF\
"    err,data readfile(path);"                                                      CRLF\
                                                                                    CRLF\
"DESCRIPTION"                                                                       CRLF\
"    The readfile() function opens the file whose name is the string pointed to"    CRLF\
"    by `path`, read all content and return."                                       CRLF\
                                                                                    CRLF\
"    The function have two return value: `err` and `data`."                         CRLF\
"    + `err`: Type of string. If not nil, it means something is wrong, no data"     CRLF\
"      read"                                                                        CRLF\
"    + `data`: Type of string. If `err` is nil, the whole file content is store"    CRLF\
"      in it."                                                                      CRLF\
)

#ifdef __cplusplus
extern "C" {
#endif

int merger_lua_api_readfile(lua_State* L);

#ifdef __cplusplus
}
#endif
#endif
