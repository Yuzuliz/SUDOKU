#pragma once
#include "File_Operation.h"

Write_File::Write_File(string file)
{
	cout << "进入写文件打开进程" << endl;
	// 输出
	this->WriteFile.open(file, ios::out|ios::app);
	if(!this->WriteFile.is_open()) 
	{
		throw "文件打开失败";
	}
	cout << "写文件打开成功" << endl;
}

Write_File::~Write_File()
{
	this->WriteFile.close();
}

bool Write_File::write_data()
{
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			this->WriteFile << this->board[i][j] << " ";
		this->WriteFile << endl;
	}
	return true;
}

bool Write_File::write_data(string result)
{
	this->WriteFile << result;
	return true;
}

Read_File::Read_File(string file)
{
	// 输入
	this->ReadFile.open(file, ios::in);
}

Read_File::~Read_File()
{
	this->ReadFile.close();
}

bool Read_File::read_data()
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
		{
			this->ReadFile >> this->board[i][j];
			if (this->board[i][j] == '$') this->board[i][j] = '0';
		}	
	return true;
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