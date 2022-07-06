#ifndef __MERGER_FILE_H__
#define __MERGER_FILE_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ev_dirent_type_e
{
    EV_DIRENT_UNKNOWN,
    EV_DIRENT_FILE,
    EV_DIRENT_DIR,
    EV_DIRENT_LINK,
    EV_DIRENT_FIFO,
    EV_DIRENT_SOCKET,
    EV_DIRENT_CHR,
    EV_DIRENT_BLOCK
}ev_dirent_type_t;

typedef struct ev_dirent_s
{
    char*               name;   /**< Entry name */
    ev_dirent_type_t    type;   /**< Entry type */
}ev_dirent_t;

/**
 * @brief Readdir callback.
 * @param[in] info      Dirent information.
 * @param[in] arg       User defined data.
 * @return              non-zero to stop.
 */
typedef int (*ev_fs_readdir_cb)(ev_dirent_t* info, void* arg);

/**
 * @brief Read file content into \p data.
 * @param[in] file  File path.
 * @param[out] data File content, terminate byte is appended. use free() to release it.
 * @param[out] size File content size, not including terminate byte.
 * @return  0 if success, otherwise failed.
 */
int cmerge_read_file(const char* file, char** data, size_t* size);

int cmerge_write_file(const char* file, const void* data, size_t size);

#ifdef __cplusplus
}
#endif

#endif
