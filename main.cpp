//
// Created by Borbély László on 2018. 09. 15..
//

#include <vector>
#include <getopt.h>
#include <sudookuController.h>
#include <handlers/input_handlers/fileInputHandler.h>
#include <handlers/output_handlers/fileOutputHandler.h>

int main(int argc, char *argv[]) {
    bool dflag = false;
    int c;

    while ((c = getopt(argc, argv, "dp:")) != -1)
        switch (c) {
            case 'd':
                dflag = true;
                break;
            case '?':
                if (optopt == 'p')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
            default:
                abort();
        }

    FileInputHandler fileInputHandler{{dflag}, argv[optind]};
    FileOutputHandler fileOutputHandler{"solutions.txt"};
    Solver solver{};

    SudookuController sudookuController{&fileInputHandler, &fileOutputHandler, &solver};
    sudookuController.run();

    return 0;
}