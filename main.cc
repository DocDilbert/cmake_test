#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
    static int verbose_flag;
    int c;

    while (1)
    {
        static struct option long_options[] =
        {
            {L"verbose", ARG_NONE, &verbose_flag, 1},
            {L"brief",   ARG_NONE, &verbose_flag, 0},
            {L"add",     ARG_NONE, 0, L'a'},
            {L"append",  ARG_NONE, 0, L'b'},
            {L"delete",  ARG_REQ,  0, L'd'},
            {L"create",  ARG_REQ,  0, L'c'},
            {L"file",    ARG_REQ, 0 , L'f'},
            { ARG_NULL , ARG_NULL , ARG_NULL , ARG_NULL }
        };

        int option_index = 0;
        c = getopt_long(argc, argv, L"abc:d:f:", long_options, &option_index);

        // Check for end of operation or error
        if (c == -1)
            break;

        // Handle options
        switch (c)
        {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            wprintf(L"option %s", long_options[option_index].name);
            if (optarg)
                wprintf(L" with arg %s", optarg);
            wprintf(L"\n");
            break;

        case L'a':
            wprintf(L"option -a\n");
            break;

        case L'b':
            wprintf(L"option -b\n");
            break;

        case L'c':
            wprintf(L"option -c with value `%s'\n", optarg);
            break;

        case L'd':
            wprintf(L"option -d with value `%s'\n", optarg);
            break;

        case L'f':
            wprintf(L"option -f with value `%s'\n", optarg);
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            abort();
        }
    }

    if (verbose_flag)
        wprintf(L"verbose flag is set\n");


    if (optind < argc)
    {
        wprintf(L"non-option ARGV-elements: ");
        while (optind < argc) wprintf(L"%s ", argv[optind++]);
        wprintf(L"\n");
    }
    return 0;
}