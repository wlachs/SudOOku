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
    /* Input file name variable */
    const char *inputFileName = nullptr;

    /* Output file name variable */
    const char *outputFileName = "solutions.txt";

    /* Check whether the flag for DiagonalStrategy is set */
    bool diagonalStrategyFlag = false;

    /* Local variable for parsing command line parameters */
    int commandLineParameter;

    /* Parse command line parameters */
    while ((commandLineParameter = getopt(argc, argv, "i:o:d")) != -1)
        switch (commandLineParameter) {
            case 'i':
                /* Handle -i flag */
                if (optarg) {
                    /* If there is a value provided, set input file value */
                    inputFileName = optarg;
                }
                break;

            case 'o':
                /* Handle -o flag */
                if (optarg) {
                    /* If there is a value provided, set output file value */
                    outputFileName = optarg;
                }
                break;

            case 'd':
                /* If the '-d' flag is set, use DiagonalStrategy */
                diagonalStrategyFlag = true;
                break;

                /* Otherwise, abort execution */
            default:
                abort();
        }

    /* If there is no input file name specified, terminate */
    if (inputFileName == nullptr) {
        return 2;
    }

    /* Initialize classes for puzzle solving
     * The path of the input file is also passed as a command line parameter */
    FileInputHandler fileInputHandler{{diagonalStrategyFlag}, inputFileName};

    /* Specify output file name */
    FileOutputHandler fileOutputHandler{outputFileName};

    /* Initialize solver */
    Solver solver{};

    /* Initialize controller with the necessary parameters */
    SudookuController sudookuController{&fileInputHandler, &fileOutputHandler, &solver};

    /* Start the program */
    sudookuController.run();

    return 0;
}