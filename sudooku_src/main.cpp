//
// Created by Borbély László on 2018. 09. 15..
//

#include <vector>
#include <getopt.h>
#include <sudookuController.h>
#include <handlers/input_handlers/fileInputHandler.h>
#include <handlers/output_handlers/fileOutputHandler.h>

/**
 * Main application function
 * Parses command line arguments, initializes the application and starts execution
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    /* Check whether the flag for DiagonalStrategy is set */
    bool diagonalStrategyFlag = false;

    /* Local variable for parsing command line parameters */
    int commandLineParameter;

    /* Parse command line parameters */
    while ((commandLineParameter = getopt(argc, argv, "dp:")) != -1)
        switch (commandLineParameter) {
            /* If the '-d' flag is set, use DiagonalStrategy */
            case 'd':
                diagonalStrategyFlag = true;
                break;

                /* In case of an unknown flag, notify user on the standard error output */
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

                /* Otherwise, abort execution */
            default:
                abort();
        }

    /* Initialize classes for puzzle solving
     * The path of the input file is also passed as a command line parameter */
    FileInputHandler fileInputHandler{{diagonalStrategyFlag}, argv[optind]};

    /* Specify output file name */
    /* TODO: get output file name as a command line parameter */
    FileOutputHandler fileOutputHandler{"solutions.txt"};

    /* Initialize solver */
    Solver solver{};

    /* Initialize controller with the necessary parameters */
    SudookuController sudookuController{&fileInputHandler, &fileOutputHandler, &solver};

    /* Start the program */
    sudookuController.run();

    return 0;
}