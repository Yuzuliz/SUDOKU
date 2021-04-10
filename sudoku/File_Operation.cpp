#include "File_Operation.h"
using namespace std;

Write_File::Write_File(string file)
{
	// 输出
	this->WriteFile.open(file, ios::out|ios::app);
	if(!WriteFile.is_open()) 
	{
		throw "文件打开失败";
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			board[i][j] = '0';
}

Write_File::~Write_File()
{
	this->WriteFile.close();
}

bool Write_File::write_data()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			this->WriteFile << board[i][j] << " ";
		this->WriteFile << endl;
	}
}

Read_File::Read_File(string file)
{
	// 输入
	this->ReadFile.open(file, ios::in);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			board[i][j] = '0';
}

Read_File::~Read_File()
{
	this->ReadFile.close();
}

bool Read_File::read_data()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			this->ReadFile >> board[i][j];
}