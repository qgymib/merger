#include "misc.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define POSIX_ERRNO_TABLE(XX) \
    XX(ENOMEM, CMERGE_ENOMEM)

int cmerge_translate_sys_error(int errcode)
{
#define EXPAND_SYS_ERR_TABLE(a, b)  case (a): return (b);

    switch (errcode)
    {
    POSIX_ERRNO_TABLE(EXPAND_SYS_ERR_TABLE);
    case 0: return CMERGE_SUCCESS;
    default:
        abort();
    }

#undef EXPAND_SYS_ERR_TABLE
}

const char* cmerge_strerror(int errcode)
{
    switch (errcode)
    {
    case CMERGE_SUCCESS:    return "Operation success";
    case CMERGE_ENOMEM:     return "Not enough space/cannot allocate memory";
    default:                return "Unknown";
    }
}

char* cmerge_strdup(const char* str)
{
#if defined(_WIN32)
    return _strdup(str);
#else
    return strdup(str);
#endif
}

int pattern_matches_string(const char* pat, const char* str)
{
    switch (*pat)
    {
    case '\0':
        return *str == '\0';
    case '?':
        return *str != '\0' && pattern_matches_string(pat + 1, str + 1);
    case '*':
        return (*str != '\0' && pattern_matches_string(pat, str + 1)) || pattern_matches_string(pat + 1, str);
    default:
        return *pat == *str && pattern_matches_string(pat + 1, str + 1);
    }
}

char* file_parrent_dir(const char* path)
{
    size_t i = 0;
    const char* last_slash = NULL;

    for (; path[i] != '\0'; i++)
    {
        if (path[i] == '\\' || path[i] == '/')
        {
            last_slash = &path[i];
        }
    }

    if (last_slash == NULL)
    {
        return cmerge_strdup("");
    }

    size_t str_size = last_slash - path;
    char* buffer = malloc(str_size + 1);
    assert(buffer != NULL);

    memcpy(buffer, path, str_size);
    buffer[str_size] = '\0';

    return buffer;
}
