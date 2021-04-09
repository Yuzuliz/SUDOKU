#pragma once
#include "common.h"


class SUDOKU
{
	int board[DIM][DIM];
	string outputPath;
public:
	bool CorrectPlace(int x, int y);

	void Initial(string input="",string output="");

	void Display(string ps="");
	
	void Shift();

	bool Backtrack(int t = 0);
};

void reverse(int* arr, int begin, int end);

//×óÒÆkÎ»
void move_left(int* arr, int arr_num, int k);