#include "runtime.h"
#include "lua_finialize.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int merger_lua_api_finialize(lua_State* L)
{
    merger.finialize.code = (int)luaL_checkinteger(L, 1);

    if (merger.finialize.data != NULL)
    {
        free(merger.finialize.data);
        merger.finialize.data = NULL;
        merger.finialize.data_size = 0;
    }

    const char* data = lua_tolstring(L, 2, &merger.finialize.data_size);

    merger.finialize.data = malloc(merger.finialize.data_size);
    assert(merger.finialize.data != NULL);
    memcpy(merger.finialize.data, data, merger.finialize.data_size);

    return 0;
}
