#pragma once
#ifndef _FILEOP_H

#define _FILEOP_H

#include "common.h"

class Write_File
{
public:
	Write_File(string file);
	~Write_File();
	bool write_data();
	bool write_data(string result);
	char board[DIM][DIM];


private:
	ofstream WriteFile;

};

class Read_File
{
public:
	Read_File(string file);
	~Read_File();
	bool read_data();
	void show_board();
	char board[DIM][DIM];


private:
	ifstream ReadFile;
};

#endif // !_FILEOP_H