//
// Created by Borbély László on 2018. 09. 15..
//

#include <vector>
#include <getopt.h>
#include <sudookuController.h>
#include <handlers/input_handlers/fileInputHandler.h>
#include <handlers/output_handlers/fileOutputHandler.h>
#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_core/strategies/groupStrategy.h>
#include <sudooku_core/strategies/diagonalStrategy.h>

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

    /* Init SolvingStrategy * vector */
    std::vector<SolvingStrategy *> solvingStrategies{};

    /* Local variable for parsing command line parameters */
    int commandLineParameter;

    /* Parse command line parameters */
    while ((commandLineParameter = getopt(argc, argv, "i:o:rcgd")) != -1)
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

            case 'r':
                /* If the '-r' flag is set, use RowStrategy */
                solvingStrategies.push_back(new RowStrategy{});
                break;

            case 'c':
                /* If the '-c' flag is set, use ColumnStrategy */
                solvingStrategies.push_back(new ColumnStrategy{});
                break;

            case 'g':
                /* If the '-g' flag is set, use GroupStrategy */
                solvingStrategies.push_back(new GroupStrategy{});
                break;

            case 'd':
                /* If the '-d' flag is set, use DiagonalStrategy */
                solvingStrategies.push_back(new DiagonalStrategy{});
                break;

                /* Otherwise, abort execution */
            default:
                abort();
        }

    /* If there is no input file name specified, terminate */
    if (inputFileName == nullptr) {
        return 2;
    }

    /* Check whether there are any rules explicitly selected */
    if (solvingStrategies.empty()) {
        /* If not, set initial settings */
        solvingStrategies.push_back(new RowStrategy{});
        solvingStrategies.push_back(new ColumnStrategy{});
        solvingStrategies.push_back(new GroupStrategy{});
    }

    /* Initialize classes for puzzle solving
     * The path of the input file is also passed as a command line parameter */
    FileInputHandler fileInputHandler{solvingStrategies, inputFileName};

    /* Specify output file name */
    FileOutputHandler fileOutputHandler{outputFileName};

    /* Initialize solver */
    Solver solver{};

    /* Initialize controller with the necessary parameters */
    SudookuController sudookuController{&fileInputHandler, &fileOutputHandler, &solver};

    /* Start the program */
    sudookuController.run();

    /* Deallocate SolvingStrategy pointers */
    for (SolvingStrategy *solvingStrategy : solvingStrategies) {
        /* Delete object */
        delete solvingStrategy;
    }

    return 0;
}