#pragma once
#include <iostream>
#include <fstream>
using namespace std;


class SUDOKU
{
	int board[9][9];
	string outputPath;
public:
	bool CorrectPlace(int x, int y);

	void Initial(string input="",string output="");

	void Display(string ps="");

	bool Backtrack(int t = 0);
};

