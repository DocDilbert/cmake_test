#include <stdio.h>
#include <stdlib.h>
#include <QApplication>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <getopt.h>
#include "mainwindow.h"


int main(int argc, char* argv[]) 
{
    static int verbose_flag;
    int c;

    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose", ARG_NONE, &verbose_flag, 1},
            {"brief",   ARG_NONE, &verbose_flag, 0},
            {"add",     ARG_NONE, 0, 'a'},
            {"append",  ARG_NONE, 0, 'b'},
            {"delete",  ARG_REQ,  0, 'd'},
            {"create",  ARG_REQ,  0, 'c'},
            {"file",    ARG_REQ, 0 , 'f'},
            { ARG_NULL , ARG_NULL , ARG_NULL , ARG_NULL }
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "abc:d:f:", long_options, &option_index);

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
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 'a':
            printf("option -a\n");
            break;

        case 'b':
            printf("option -b\n");
            break;

        case 'c':
            printf("option -c with value `%s'\n", optarg);
            break;

        case 'd':
            printf("option -d with value `%s'\n", optarg);
            break;

        case 'f':
            printf("option -f with value `%s'\n", optarg);
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            abort();
        }
    }

    if (verbose_flag)
        printf("verbose flag is set\n");


    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc) printf("%s ", argv[optind++]);
        printf("\n");
    }
  //  typedef std::istream_iterator<int> in;

 //   std::cout << "Type in any number: ";

   // std::for_each(
    //    in(std::cin), in(), std::cout
   //     << (boost::lambda::_1 * 10)
  //      << "\nType in another number: ");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
