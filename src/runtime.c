#include "runtime.h"
#include "misc.h"
#include "lua_api.h"
#include <string.h>
#include <stdlib.h>

merger_runtime_t merger;

static const char* s_help =
"merger - Merge two or more files into one big file."                           CRLF
"Usage: merger [OPTIONS] -c [PATH_TO_CONFIG] -o [PATH_TO_OUTPUT]"               CRLF
"OPTIONS:"                                                                      CRLF
"  -c,--config"                                                                 CRLF
"      Path to configuration file."                                             CRLF
"  -o,--output"                                                                 CRLF
"      Path to output file."                                                    CRLF
"  -m,--man"                                                                    CRLF
"      Show document about function and exit."                                  CRLF
"  --list-api"                                                                  CRLF
"      List builtin functions and exit."                                        CRLF
"      Access API by using `merger.API_NAME`."                                  CRLF
"  -h,--help"                                                                   CRLF
"      Show this help and exit."                                                CRLF
                                                                                CRLF
;

static int _check_options(void)
{
    if (merger.config_path == NULL)
    {
        fprintf(stderr, "missing configuration file.\n");
        return -1;
    }

    if (merger.output_path == NULL)
    {
        fprintf(stderr, "missing output file.\n");
        return -1;
    }

    return 0;
}

static int _parser_options(int argc, char* argv[])
{
    int i;
    const char* opt;
    int exit_result = EXIT_SUCCESS;

    for (i = 1; i < argc; i++)
    {
        /*
         * -h,--help
         */
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            goto show_help_and_exit;
        }

        /*
         * -m.--man
         */
        if (strcmp(argv[i], "-m") == 0)
        {
            if (i == argc - 1)
            {
                fprintf(stderr, "missing argument to `-m`\n");
                exit_result = EXIT_FAILURE;
                goto cleanup_and_exit;
            }

            opt = argv[i + 1];
            goto show_man_and_exit;
        }

        opt = "--man=";
        if (strncmp(argv[i], opt, strlen(opt)) == 0)
        {
            opt = argv[i] + strlen(opt);
            goto show_man_and_exit;
        }

        /*
         * --list-api
         */
        if (strcmp(argv[i], "--list-api") == 0)
        {
            goto list_api_and_exit;
        }

        /*
         * -c,--config
         */
        if (strcmp(argv[i], "-c") == 0)
        {
            if (i == argc - 1)
            {
                fprintf(stderr, "missing argument to `-c`\n");
                exit_result = EXIT_FAILURE;
                goto cleanup_and_exit;
            }

            i++;
            merger.config_path = argv[i];
            continue;
        }

        opt = "--config=";
        if (strncmp(argv[i], opt, strlen(opt)) == 0)
        {
            merger.config_path = argv[i] + strlen(opt);
            continue;
        }

        /*
         * -o,--output
         */
        if (strcmp(argv[i], "-o") == 0)
        {
            if (i == argc - 1)
            {
                fprintf(stderr, "missing argument to `-o`\n");
                exit_result = EXIT_FAILURE;
                goto cleanup_and_exit;
            }

            i++;
            merger.output_path = argv[i];
            continue;
        }

        opt = "--output=";
        if (strncmp(argv[i], opt, strlen(opt)) == 0)
        {
            merger.output_path = argv[i] + strlen(opt);
            continue;
        }

        /*
         * Unknown option
         */
        fprintf(stderr, "unknown option `%s`\n", argv[i]);
        exit_result = EXIT_FAILURE;
        goto cleanup_and_exit;
    }

    if (_check_options())
    {
        exit_result = EXIT_FAILURE;
        goto cleanup_and_exit;
    }

    return 0;

show_help_and_exit:
    printf("%s", s_help);
    goto cleanup_and_exit;

show_man_and_exit:
    merger_show_help(opt);
    goto cleanup_and_exit;

list_api_and_exit:
    merger_list_builtin();
    goto cleanup_and_exit;

cleanup_and_exit:
    merger_runtime_exit();
    exit(exit_result);
}

int merger_runtime_init(int argc, char* argv[])
{
    memset(&merger, 0, sizeof(merger));

    _parser_options(argc, argv);

    if ((merger.L = luaL_newstate()) == NULL)
    {
        LOG_ERROR("luaL_newstate failure.");
        return -1;
    }

    return 0;
}

void merger_runtime_exit(void)
{
    if (merger.L != NULL)
    {
        lua_close(merger.L);
        merger.L = NULL;
    }
}
