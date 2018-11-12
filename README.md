# SudOOku
[![Build Status](https://travis-ci.org/wlchs/SudOOku.svg?branch=master)](https://travis-ci.org/wlchs/SudOOku)
[![Coverage Status](https://coveralls.io/repos/github/wlchs/SudOOku/badge.svg?branch=master)](https://coveralls.io/github/wlchs/SudOOku?branch=master)
[![CodeFactor](https://www.codefactor.io/repository/github/wlchs/sudooku/badge)](https://www.codefactor.io/repository/github/wlchs/sudooku)
[![Sonarcloud Status](https://sonarcloud.io/api/project_badges/measure?project=wlchs_SudOOku&metric=alert_status)](https://sonarcloud.io/dashboard?id=wlchs_SudOOku)

Object-oriented Sudoku solver ~~& generator~~
#### Version: 1.1.0b

## Solver
- implemented
- *verification rules* defined in the strategies
- slow, if only the *verification rules* are defined
- faster, if *optimization strategies* are also provided

## Generator
- not implemented yet

## Testing
 - numerous test inputs in [```sudooku_tests/testInputs```](https://github.com/wlchs/SudOOku/tree/master/sudooku_tests/testInputs)
 - unit tests for the following classes already implemented:
    - ```Field```
    - ```ForkHelper```
    - ```Matrix```
    - ```Solver```
    - ```ColumnStrategy```
    - ```RowStrategy```
    - ```GroupStrategy```
    - ```DiagonalStrategy```
    - ```SudookuController```
    - ```FileInputHandler```
    - ```FileOutputHandler```
    - ```ReadMatrixFromFile```
    - ```PrintMatrixToFile```