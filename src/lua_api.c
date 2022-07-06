#include "misc.h"
#include "lua_api.h"
#include "lua_findfile.h"
#include "lua_finialize.h"
#include "lua_readfile.h"
#include "lua_sha256.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Register Lua API here.
 * The Lua API must have following parameters in order:
 * + name:  The name of API.
 * + func:  Function pointer to C function.
 * + brief: Brief document.
 * + docs:  Detail document.
 */
#define MERGER_LUA_APIS(XX)    \
    MERGER_LUA_API_FINDFILE(XX)     \
    MERGER_LUA_API_FINIALIZE(XX)    \
    MERGER_LUA_API_READFILE(XX)     \
    MERGER_LUA_API_SHA256(XX)

typedef struct merger_lua_api_doc
{
    const char*     name;       /**< Function name */
    const char*     brief;      /**< Brief document. */
    const char*     document;   /**< Detail document. */
} merger_lua_api_doc_t;

/*
 * Lua library
 */
#define MERGER_LUA_API_EXPAND_AS_LUAL_REG(name, func, brief, document)  \
    { name, func },
static const luaL_Reg s_merger_lib[] = {
    MERGER_LUA_APIS(MERGER_LUA_API_EXPAND_AS_LUAL_REG)
};
#undef MERGER_LUA_API_EXPAND_AS_LUAL_REG

/*
 * Document for API
 */
#define MERGER_LUA_API_EXPAND_AS_RECORD(name, func, brief, document)    \
    { name, brief, document },
static const merger_lua_api_doc_t s_merger_docs[] = {
    MERGER_LUA_APIS(MERGER_LUA_API_EXPAND_AS_RECORD)
};
#undef MERGER_LUA_API_EXPAND_AS_RECORD

static int _load_cfunctions(lua_State* L)
{
    luaL_newlib(L, s_merger_lib);
    return 1;
}

void merger_load_libs(lua_State* L)
{
    luaL_requiref(L, "merger", _load_cfunctions, 1);
    lua_pop(L, 1);
}

void merger_show_help(const char* func)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(s_merger_docs); i++)
    {
        if (strcmp(func, s_merger_docs[i].name) == 0)
        {
            if (s_merger_docs[i].document != NULL && strlen(s_merger_docs[i].document) != 0)
            {
                printf("%s - %s\n\n%s", func, s_merger_docs[i].brief, s_merger_docs[i].document);
            }
            else
            {
                printf("%s - %s", func, s_merger_docs[i].brief);
            }
        }
    }
}

void merger_list_builtin(void)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(s_merger_docs); i++)
    {
        printf("%s - %s\n", s_merger_docs[i].name, s_merger_docs[i].brief);
    }
}
