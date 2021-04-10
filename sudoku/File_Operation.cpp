#pragma once
#include "File_Operation.h"

Write_File::Write_File(string file)
{
	// 输出
	this->WriteFile.open(file, ios::out);
	if(!this->WriteFile.is_open()) 
	{
		throw "输出文件打开失败";
	}
	cout << "输出文件打开成功" << endl;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			this->board[i][j] = 0;
}

Write_File::~Write_File()
{
	this->WriteFile.close();
}

bool Write_File::write_data()
{
	// 将数据成员写入到文件中
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			this->WriteFile << this->board[i][j] << " ";
		this->WriteFile << endl;
	}
	return 1;
}

bool Write_File::write_data(string result)
{
	this->WriteFile << result;
	return 1;
}

Read_File::Read_File(string file)
{
	// 输入
	this->ReadFile.open(file, ios::in);
	cout << "输入文件为" << file << endl;
	if (!this->ReadFile.is_open())
	{
		throw "输入文件打开失败";
	}
	cout << "输入文件打开成功" << endl;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			this->board[i][j] = 0;
}

Read_File::~Read_File()
{
	this->ReadFile.close();
}

bool Read_File::read_data()
{
	// 从文件中读数据
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
		{
			// 如果已经没有DIM×DIM了，读取失败，返回0
			if (this->ReadFile.eof()) return 0;
			this->ReadFile >> this->board[i][j];
			if (this->board[i][j] == '$') this->board[i][j] = '0';
		}
	return 1;
}

string Read_File::get_first_line()
{
	string str(board[0]);
	return str;
}

bool Read_File::read_eof()
{
	if (this->ReadFile.eof()) return 1;
	return 0;
}

void Read_File::show_board()
{
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			cout << this->board[i][j] << " ";
		cout << endl;
	}
}

void change_char_2_int(char board1[DIM][DIM], int board2[DIM][DIM])
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
		{
			board2[i][j] = board1[i][j] - '0';
		}
}