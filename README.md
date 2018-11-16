# SudOOku
[![Build Status](https://travis-ci.org/wlchs/SudOOku.svg?branch=master)](https://travis-ci.org/wlchs/SudOOku)
[![Coverage Status](https://coveralls.io/repos/github/wlchs/SudOOku/badge.svg?branch=master)](https://coveralls.io/github/wlchs/SudOOku?branch=master)
[![CodeFactor](https://www.codefactor.io/repository/github/wlchs/sudooku/badge)](https://www.codefactor.io/repository/github/wlchs/sudooku)
[![Sonarcloud Status](https://sonarcloud.io/api/project_badges/measure?project=wlchs_SudOOku&metric=alert_status)](https://sonarcloud.io/dashboard?id=wlchs_SudOOku)

Object-oriented Sudoku solver ~~& generator~~
#### Version: 1.2.1

## How to make it work?
First, clone this repository to your computer using the following command:
```bash
git clone https://github.com/wlchs/SudOOku
```

Then checkout the ```master``` branch. It is also possible to use another branches,
but please be aware that these might not work as expected.

To checkout a branch, use the following command (in this case we use ```master``` as an example):
```bash
git checkout master
```

Now you have to compile the project.

First, navigate to the repository you just cloned:
```bash
cd /path_to_this_repository/
```

If you haven't changed anything, the name should be ```SudOOku```, so the command looks like this:
```bash
cd SudOOku
```

Then finally compile the project with the following two commands:
```bash
cmake .
cmake --build .
```

The executable can be found in the ```bin``` folder.

## How to use?
Congratulations, if you read this, it means you successfully downloaded and compiled the project.
The next step is to learn how to use it.

### 1. Input format
The puzzle to be solved must be of a certain format. The file provided should contain the initial
values of the puzzle separated by semicolons. 

Example input file:
```text
1;;3;4;
4;3;;1;
;;;;
;1;;2;
```

Which is equal to the puzzle:
```text
1   3 4
4 3   1

  1   2
```

Empty lines of the input or lines starting with ```#``` will be considered as comments
and will be ignored.

It is also possible to provide multiple puzzles in a single input file (even with different dimensions):
```text
1;;;;
2;;;;
3;;;;
;;;;
1;2;3;;
;;;;
;;;;
;;;;
```
or with comments and empty lines between:
```text
## Puzzle 1
1;;;;
2;;;;
3;;;;
;;;;

#########

## Puzzle 2
1;2;3;;
;;;;
;;;;
;;;;
```

### 2. Run
When running the application, there are several command line parameters which can be (or must be)
provided.

#### Input file: ```-i```
To specify the input file, use the ```-i``` flag.
Example:
```bash
./SudOOku -i input.mat
```

#### Output file: ```-o``` (optional)
To specify the output file, use the ```-o``` flag.
Example:
```bash
./SudOOku -i input.mat -o output.mat
```

Please note, if there is no output file specified, the default name is ```solutions.txt```.

#### Solver flags: ```-r```, ```-c```, ```-g```, ```-d``` (optional)
To specify the solving strategies, use the following flags: ```-r```, ```-c```, ```-g```, ```-d```.

##### Row: ```-r```
 - a value can appear once in a row
##### Column: ```-c```
 - a value can appear once in a column
##### Group: ```-g```
 - a value can appear once in a group
##### Diagonal: ```-d```
 - a value can appear once in a diagonal of the Matrix

Example:
```bash
./SudOOku -i input.mat -rcgd
```

The default strategies are: ```-rcg```.

### 3. Output format
The output is identical to the input.

Solution of the first example puzzle above:
```text
## Solutions for puzzle 1
1;2;3;4;
4;3;2;1;
2;4;1;3;
3;1;4;2;

#########
```

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

To run the tests, compile the project and execute the following command:
```bash
ctest
```