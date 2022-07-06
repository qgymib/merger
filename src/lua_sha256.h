#ifndef __MERGER_LUA_API_SHA256_H__
#define __MERGER_LUA_API_SHA256_H__

#include "lua_api.h"

#define MERGER_LUA_API_SHA256(XX)                                                       \
XX(                                                                                     \
"sha256", merger_lua_api_sha256, "Calculate SHA256 of given data.",                     \
"SYNOPSIS"                                                                          CRLF\
"    string sha256(data);"                                                          CRLF\
                                                                                    CRLF\
"DESCRIPTION"                                                                       CRLF\
"    The sha256() function read content of `data` and calculate SHA256 for it."     CRLF\
)

#ifdef __cplusplus
extern "C" {
#endif

int merger_lua_api_sha256(lua_State* L);

#ifdef __cplusplus
}
#endif
#endif
