# Sudoku

* Programme / Submit : Sublime Text 3.1.1, macOS Sierra 10.12.6.
* Debug / Analysis / Complie : Visual Studio 2017, Windows 10 Professional.


## Directory

```
BIN/
Sudoku.exe                          Executable program for Windows x64
Debug Tools/
SudokuVerify.cpp                    Source code for verifying sudoku
Verify                              Executable program (macOS) for verifying sudoku
UnsolvedSudoku.txt                  Unsolved sudoku file for SolveSudoku() function testing
sudoku.cpp                              Source code
```

## Tutorial
Sudoku.exe can create / solve sudoku.
- To create, use command `-c <n>`, n must be a number between 1 - 1000000). The created sudoku will be saved in a .txt file named "sudoku.txt" in current path.
- To solve, use command `-s <path>`, path is the path of .txt file in which the unsolved sudoku saved.

## Debug Tools instructions
- Verify

Put generated .txt file and Verify program in the same directory.
Execute Verify and enter the .txt file name.
If any of the sudoku in .txt file is wrong, the program will prompt you.

- UnsolvedSudoku.txt

UnsolvedSudoku.txt is used for SolveSudoku() function testing as input file.

#### [ More Infomation ](https://blog.csdn.net/acromema/article/details/84571659)

