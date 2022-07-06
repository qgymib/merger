#include "sha256.h"
#include "misc.h"
#include "lua_sha256.h"

int merger_lua_api_sha256(lua_State* L)
{
    size_t data_len = 0;
    const char* data = lua_tolstring(L, 1, &data_len);

    sha256_ctx_t ctx;
    sha256_init(&ctx);

    sha256_update(&ctx, data, data_len);

    uint8_t hash_val[32];
    sha256_final(&ctx, hash_val);

    char buffer[65];
    size_t i;
    for (i = 0; i < ARRAY_SIZE(hash_val); i++)
    {
        snprintf(buffer + 2 * i, 3, "%02X", hash_val[i]);
    }

    lua_pushstring(L, buffer);
    return 1;
}
