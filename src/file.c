#include "file.h"
#include "misc.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if defined(_WIN32)
#   include <windows.h>
#endif

int cmerge_read_file(const char* file, char** data, size_t* size)
{
    int errcode;
    FILE* file_handle;

#if defined(_WIN32)
    errcode = fopen_s(&file_handle, file, "rb");
#else
    file_handle = fopen(file, "rb");
    errcode = errno;
#endif
    
    if (file_handle == NULL)
    {
        return cmerge_translate_sys_error(errcode);
    }

    if (fseek(file_handle, 0, SEEK_END) < 0)
    {
        errcode = errno;
        fclose(file_handle);
        return cmerge_translate_sys_error(errcode);
    }

    /* Get file size */
    long file_size = ftell(file_handle);
    assert(file_size >= 0);
    rewind(file_handle);

    if ((*data = malloc((size_t)file_size + 1)) == NULL)
    {
        fclose(file_handle);
        return CMERGE_ENOMEM;
    }

    size_t read_count = fread(*data, file_size, 1, file_handle);
    assert(read_count == 1);
    (*data)[file_size] = '\0';

    fclose(file_handle);
    *size = file_size;

    return CMERGE_SUCCESS;
}

int cmerge_write_file(const char* file, const void* data, size_t size)
{
    FILE* pfile = NULL;
    int errcode = 0;

#if defined(_WIN32)
    errcode = fopen_s(&pfile, file, "wb");
#else
    pfile = fopen(file, "wb");
    errcode = errno;
#endif

    if (pfile == NULL)
    {
        char* str_err = malloc(ERROR_MSG_SIZE);
        assert(str_err != NULL);
        strerror_r(errcode, str_err, ERROR_MSG_SIZE);
        fprintf(stderr, "can not open `%s`: %s(%d)\n", file, str_err, errcode);
        free(str_err);

        return -1;
    }

    size_t write_num = fwrite(data, size, 1, pfile);
    fclose(pfile);

    if (write_num != 1)
    {
        return -1;
    }

    return 0;
}
