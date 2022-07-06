#ifndef __CMERGE_MISC_H__
#define __CMERGE_MISC_H__

#if !defined(container_of)
#   if defined(__GNUC__) || defined(__clang__)
#   define container_of(ptr, type, member)   \
        ({ \
            const typeof(((type *)0)->member)*__mptr = (ptr); \
            (type *)((char *)__mptr - offsetof(type, member)); \
        })
#   else
#   define container_of(ptr, type, member)   \
        ((type *) ((char *) (ptr) - offsetof(type, member)))
#   endif
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define CRLF                    "\n"
#define LOG_ERROR(fmt, ...)     fprintf(stderr, "[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define ERROR_MSG_SIZE          1024

#if defined(_WIN32)
#   define strerror_r(errnum, buf, buflen)  strerror_s(buf, buflen, errnum)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum cmerge_errno
{
    CMERGE_SUCCESS  =  0,
    CMERGE_ENOMEM   = -12,
}cmerge_errno_t;

/**
 * @brief Translate system error code to #cmerge_errno_t.
 * @param[in] errcode   System error code.
 * @return              #cmerge_errno_t
 */
int cmerge_translate_sys_error(int errcode);

/**
 * @brief Translate errcode to C string.
 * @param[in] errcode   Return code from #cmerge_translate_sys_error()
 * @return              C string.
 */
const char* cmerge_strerror(int errcode);

/**
 * @brief Same as strdup().
 */
char* cmerge_strdup(const char* str);

/**
 * @brief Check if `str` match `pat`
 * @return bool
 */
int pattern_matches_string(const char* pat, const char* str);

/**
 * @brief Get parrent dir.
 * Use #free() to release result.
 */
char* file_parrent_dir(const char* path);

#ifdef __cplusplus
}
#endif

#endif
