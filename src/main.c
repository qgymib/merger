#include "runtime.h"
#include "misc.h"
#include "file.h"
#include "lua_api.h"
#include <stdlib.h>

static void _at_exit(void)
{
    merger_runtime_exit();
}

static int lua_loader(lua_State* L)
{
    int status = LUA_OK;

    luaL_openlibs(L);
    merger_load_libs(L);

    status = luaL_dofile(L, merger.config_path);

    if (status != LUA_OK)
    {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        goto fin;
    }

fin:
    lua_pushinteger(L, status);
    return 1;
}

int main(int argc, char* argv[])
{
    if (merger_runtime_init(argc, argv) != 0)
    {
        return EXIT_FAILURE;
    }

    atexit(_at_exit);

    lua_pushcfunction(merger.L, lua_loader);
    int status = lua_pcall(merger.L, 0, 1, 0);

    if (status != LUA_OK)
    {
        fprintf(stderr, "lua script execution failed: %d\n", status);
        return EXIT_FAILURE;
    }

    if (merger.finialize.code != 0)
    {
        fprintf(stderr, "merge failed: %s\n", merger.finialize.data);
        return EXIT_FAILURE;
    }

    if (cmerge_write_file(merger.output_path, merger.finialize.data,
        merger.finialize.data_size) != 0)
    {
        fprintf(stderr, "failed to write to `%s`\n", merger.output_path);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
