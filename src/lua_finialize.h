#ifndef __MERGER_LUA_API_FINIALIZE_H__
#define __MERGER_LUA_API_FINIALIZE_H__

#include "lua_api.h"

#define MERGER_LUA_API_FINIALIZE(XX)    \
XX(\
"finialize", merger_lua_api_finialize, "Finsh merge process and set result.",           \
"SYNOPSIS"                                                                          CRLF\
"    finialize(code, data);"                                                        CRLF\
                                                                                    CRLF\
"DESCRIPTION"                                                                       CRLF\
"    The finialize() function terminal the merge process, and write result to"      CRLF\
"    output file."                                                                  CRLF\
                                                                                    CRLF\
"    If `code` is 0, `data` must the content of output file. If `code` is not"      CRLF\
"    zero, `data` must the error message you want to print."                        CRLF\
                                                                                    CRLF\
"    You can call this function many times, but only the last time take effect."    CRLF\
                                                                                    CRLF\
"EXAMPLE"    CRLF\
""      CRLF\
)

#ifdef __cplusplus
extern "C" {
#endif

int merger_lua_api_finialize(lua_State* L);

#ifdef __cplusplus
}
#endif
#endif
