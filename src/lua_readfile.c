#include "file.h"
#include "misc.h"
#include "lua_readfile.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

int merger_lua_api_readfile(lua_State* L)
{
    char* str_err = NULL;
    char* str_data = NULL;
    const char* path = luaL_checkstring(L, 1);

    size_t data_size;
    if (cmerge_read_file(path, &str_data, &data_size) != 0)
    {
        str_err = malloc(ERROR_MSG_SIZE);
        assert(str_err != NULL);

        strerror_r(errno, str_err, ERROR_MSG_SIZE);

        lua_pushfstring(L, "%s(%d)", str_err, errno);
        lua_pushnil(L);

        goto fin;
    }

    lua_pushnil(L);
    lua_pushlstring(L, str_data, data_size);

fin:
    if (str_err != NULL)
    {
        free(str_err);
    }
    if (str_data != NULL)
    {
        free(str_data);
    }
    return 2;
}
