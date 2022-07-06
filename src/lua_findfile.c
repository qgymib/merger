#include "lua_findfile.h"
#include "misc.h"
#include "map.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct file_record
{
    ev_map_node_t   node;       /**< Map node */
#if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable : 4200)
#endif
    char            filename[]; /**< File name */
#if defined(_MSC_VER)
#    pragma warning(pop)
#endif
}file_record_t;

typedef void (*fn_find_file)(const char* filename, void* arg);

#if defined(_WIN32)

#include <windows.h>

static void _lua_api_findfile(const char* path, fn_find_file cb, void* arg)
{
    WIN32_FIND_DATAA info;

    HANDLE dir_handle = FindFirstFileA(path, &info);
    if (dir_handle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    do
    {
        if (strcmp(info.cFileName, ".") == 0 || strcmp(info.cFileName, "..") == 0)
        {
            continue;
        }

        cb(info.cFileName, arg);
    } while (FindNextFileA(dir_handle, &info));

    FindClose(dir_handle);
}

#else

#include <sys/types.h>
#include <dirent.h>

static void _lua_api_findfile(const char* path, fn_find_file cb, void* arg)
{
    char* parrent_path = file_parrent_dir(path);

    DIR* p_dir = opendir(parrent_path);
    if (p_dir == NULL)
    {
        return;
    }

    struct dirent* res;
    while ((res = readdir(p_dir)) != NULL)
    {
        if (strcmp(res->d_name, ".") == 0 || strcmp(res->d_name, "..") == 0)
        {
            continue;
        }

        cb(res->d_name, arg);
    }

    closedir(p_dir);
}

#endif

static int _on_cmp_file_name(const ev_map_node_t* key1, const ev_map_node_t* key2, void* arg)
{
    (void)arg;
    file_record_t* rec1 = container_of(key1, file_record_t, node);
    file_record_t* rec2 = container_of(key2, file_record_t, node);
    return strcmp(rec1->filename, rec2->filename);
}

static void _on_file_name(const char* filename, void* arg)
{
    ev_map_t* p_table = arg;

    size_t file_name_len = strlen(filename);
    file_record_t* rec = malloc(sizeof(file_record_t) + file_name_len + 1);
    assert(rec != NULL);

    memcpy(rec->filename, filename, file_name_len + 1);
    ev_map_insert(p_table, &rec->node);
}

int merger_lua_api_findfile(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);

    ev_map_t table;
    ev_map_init(&table, _on_cmp_file_name, NULL);
    _lua_api_findfile(path, _on_file_name, &table);

    lua_newtable(L);

    ev_map_node_t* it;
    int index = 1;
    while ((it = ev_map_begin(&table)) != NULL)
    {
        file_record_t* rec = container_of(it, file_record_t, node);
        ev_map_erase(&table, it);

        lua_pushinteger(L, index);
        lua_pushstring(L, rec->filename);
        lua_settable(L, -3);

        index++;
        free(rec);
    }

    return 1;
}
