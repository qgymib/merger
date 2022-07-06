#ifndef __MERGER_LUA_API_H__
#define __MERGER_LUA_API_H__

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef __cplusplus
extern "C" {
#endif

void merger_load_libs(lua_State* L);

void merger_show_help(const char* func);

void merger_list_builtin(void);

#ifdef __cplusplus
}
#endif

#endif
