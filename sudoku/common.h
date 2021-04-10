#pragma once
#ifndef _COMMON_H

#define _COMMON_H
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <direct.h>
#include <io.h>
#include <time.h>

#include "getopt.h"                // 包含头文件
#pragma comment(lib, "getopt.lib")   // 加载静态库文件（Windows）

using namespace std;

#define DIM 9
extern int board[DIM][DIM];
extern const string dir;
extern const string Output_Path;
extern const string gen_path_end;
extern const string gen_path_start;
extern const char* optstring;

#endif // !_COMMON_H