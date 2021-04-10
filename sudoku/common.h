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

#include "getopt.h"                // ����ͷ�ļ�
#pragma comment(lib, "getopt.lib")   // ���ؾ�̬���ļ���Windows��

using namespace std;

#define DIM 9
extern int board[DIM][DIM];
extern string Output_Path;
extern const char* optstring;

#endif // !_COMMON_H