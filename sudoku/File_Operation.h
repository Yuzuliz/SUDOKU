#pragma once
#include "common.h"

enum op_type
{
	input,
	output,
};

class Write_File
{
public:
	Write_File(string file);
	~Write_File();
	bool write_data();


private:
	ofstream WriteFile;
	char board[9][9];
};

class Read_File
{
public:
	Read_File(string file);
	~Read_File();
	bool read_data();


private:
	ifstream ReadFile;
	char board[9][9];
};