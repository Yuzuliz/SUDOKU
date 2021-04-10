// Copyright 2021 Yingtong_Yu Yifei_Guo
#ifndef SUDOKU_COMMON_H_

#define SUDOKU_COMMON_H_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <direct.h>
#include <io.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "getopt.h"
#pragma comment(lib, "getopt.lib")

using namespace std;

#define DIM 9
extern int board[DIM][DIM];
extern const string dir;
extern const string Output_Path;
extern const string gen_path_end;
extern const string gen_path_start;
extern const string distinct_result;
extern const char* optstring;


#endif  // SUDOKU_COMMON_H_
