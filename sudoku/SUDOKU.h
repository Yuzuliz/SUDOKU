#pragma once

#ifndef _SUDOKU_H

#define _SUDOKU_H

#include "common.h"
#include "File_Operation.h"


class SUDOKU
{
	string outputPath;
public:
	SUDOKU(string output);

	bool CorrectPlace(int x, int y);

	void Initial(string input="",string output="");

	void Display(string ps="");

	bool Backtrack(int t = 0);
};

//��ת
void reverse(int* arr, int begin, int end);

//����kλ
void move_left(int* arr, int arr_num, int k);

//�վ�����
string align(int a[],int N=DIM);

#endif // !_SUDOKU_H