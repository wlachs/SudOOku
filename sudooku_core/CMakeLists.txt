add_library(
        sudooku_core
        matrix/matrix.cpp
        matrix/matrix.h
        matrix/field.cpp
        matrix/field.h
        strategies/solvingStrategy.h
        strategies/rowStrategy.cpp
        strategies/strategies.h
        solvers/solver.cpp
        solvers/solver.h
        strategies/columnStrategy.cpp
        strategies/groupStrategy.cpp
        matrix/forkHelper.cpp
        matrix/forkHelper.h
        matrix/matrixReader.cpp
        matrix/matrixReader.h
        strategies/columnStrategy.h strategies/groupStrategy.h strategies/rowStrategy.h)
