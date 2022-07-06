#ifndef __MERGER_RUNTIME_H__
#define __MERGER_RUNTIME_H__

#include <setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/**
 * @brief Global runtime
 */
typedef struct merger_runtime
{
    /**
     * @brief Lua State
     */
    lua_State*  L;

    /**
     * @brief Path to configuration file.
     */
    const char* config_path;

    /**
     * @brief Path to output file.
     */
    const char* output_path;

    struct
    {
        int     code;       /**< Exit code */
        char*   data;       /**< Final data */
        size_t  data_size;  /**< Final data size */
    }finialize;
} merger_runtime_t;

/**
 * @brief Global runtime library.
 */
extern merger_runtime_t merger;

/**
 * @brief Initialize runtime.
 */
int merger_runtime_init(int argc, char* argv[]);

/**
 * @brief Cleanup runtime.
 */
void merger_runtime_exit(void);


#ifdef __cplusplus
}
#endif
#endif
