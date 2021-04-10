#pragma once

#ifndef _SUDOKU_H

#define _SUDOKU_H

#include "common.h"
#include "File_Operation.h"


class SUDOKU
{
	string Output_Path;
public:
	SUDOKU() {};
	SUDOKU(string output) :Output_Path(output) {};

	bool CorrectPlace(int x, int y);

	void Initial(string output="");

	void Display(string ps="");

	bool Backtrack(int t = 0);

	bool EndGen(int end_boards,Write_File *write_out);

	bool StartGen(int start_boards, Write_File* write_out, int blanks = 25);
};

//反转
void reverse(int* arr, int begin, int end);

//左移k位
void move_left(int* arr, int arr_num, int k);

//终局生成
string align(char a[],int N=DIM);

#endif // !_SUDOKU_H