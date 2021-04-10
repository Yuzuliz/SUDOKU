#pragma once
#include "SUDOKU.h"

//void reverse(int* arr, int begin, int end)
//{
//	for (; begin < end; begin++, end--)
//	{
//		int temp = arr[begin];
//		arr[begin] = arr[end];
//		arr[end] = temp;
//	}
//}
//
////左移k位
//void move_left(int* arr, int k, int arr_num)
//{
//	k = k % arr_num;
//	reverse(arr, 0, k - 1);
//	reverse(arr, k, arr_num - 1);
//	reverse(arr, 0, arr_num - 1);
//}

string align(string a,int N)
{
	if (N <= 0 || N > 1000000) return "";
	int k = 0;
	short int shift[DIM-1] = { 3, 6, 1, 4, 7, 2, 5, 8 };
	short int index[DIM] = { 0,1,2,3,4,5,6,7,8 };
	string result = "";
	do {
		for (int i = 0; i < DIM; i++)
		{
			result = result +  a[index[i]] + ' ';
		}
		result += "\n";
		int cur_pos;
		// 根据第一行创捷后面的行
		for (int line = 1; line < DIM; line++)
		{
			cur_pos = shift[line - 1];
			// 左移得下一行
			for (int j = 0; j < DIM; j++, cur_pos++)
			{
				cur_pos = (cur_pos == DIM) ? 0 : cur_pos;
				result = result + a[index[cur_pos]] + ' ';
			}
			result += "\n";
		}
		k++;
		result += "\n";
	} while (next_permutation(index, index + DIM) && k < N);
	return result;
}

bool SUDOKU::CorrectPlace(int x, int y)
{
	if (x < 0 || x >= DIM || y < 0 || y >= DIM)
	{
		cout << "坐标位置存在问题" << endl;
		return false;
	}
	int side = sqrt(DIM);
	int up = x / side * side;
	int down = up + side;
	int left = y / side * side;
	int right = left + side;
	// 填充的是0（即当前还为空），则必没有重复
	if (board[x][y] == 0)
	{
		return true;
	}
	// 验证行中没有重复
	for (int i = 0; i < DIM; i++)
	{
		if (board[x][y] == board[i][y] && x != i)
		{
			return false;
		}
	}
	// 验证列中没有重复
	for (int i = 0; i < DIM; i++)
	{
		if (board[x][y] == board[x][i] && y != i)
		{
			return false;
		}
	}
	// 验证块中没有重复
	for (int i = up; i < down; i++)
	{
		for (int j = left; j < right; j++)
		{
			if (board[x][y] == board[i][j])
			{
				if (x != i || y != j)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void SUDOKU::Display(Write_File *write_obj, string ps)
{
	string result;
	stringstream sstream;
	sstream << ps << '\n';
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			if (board[i][j])
			{
				sstream << board[i][j] << ' ';
			}
			else
			{
				sstream << "$ ";
			}

		}
		sstream << endl;
	}
	sstream << "-------------------------\n";
	
	result = sstream.str();

	write_obj->write_data(result);
}

bool SUDOKU::EndGen(int end_boards, Read_File *read_in, Write_File *write_out)
{
	if (end_boards > 1000000 || end_boards < 1)
	{
		cout << "终局数量不在程序接受范围内" << endl;
		return 0;
	}
	string result = align(read_in->get_first_line(), end_boards);
	if (result == "")
	{
		return false;
	}
	write_out->write_data(result);
	return true;
}

bool SUDOKU::StartGen(int start_boards, Read_File* read_in, Write_File* write_out, int blanks)
{
	if (blanks < 20 || blanks > 55)
	{
		return false;
	}
	int ran_i, ran_j, i, j, k, boards;
	string result="";
	for (boards = 0; boards < start_boards; boards++)
	{
		read_in->read_data();
		for (i = 0; i < DIM; i++)
		{
			j = 0;
			while (j < 2)
			{
				ran_j = rand() % DIM;
				if (read_in->board[i][ran_j] == '$')
					continue;
				read_in->board[i][ran_j] = '$';
				j++;
			}
		}
		k = 0;
		while (k < blanks - 2*DIM)
		{
			ran_i = rand() % DIM;
			ran_j = rand() % DIM;
			if (read_in->board[ran_i][ran_j] == '$')
				continue;
			read_in->board[ran_i][ran_j] = '$';
			k++;
		}
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				result = result + read_in->board[i][j] + ' ';
			}
			result = result + '\n';
		}
		result = result + '\n';
	}
	write_out->write_data(result);
	return true;
}

bool SUDOKU::Backtrack(Write_File*write_obj, int t)
{
	if (t < 0 || t > DIM * DIM)
	{
		cout << "回溯出现问题" << endl;
		return false;
	}
	// 已经访问了棋盘上的所有位置
	if (t == DIM*DIM)
	{
		Display(write_obj, "终局状态：");
		return true;
	}
	int x = t / DIM, y = t % DIM;
	// 如果这个位置上本来就有值，那就访问下一个位置
	if (board[x][y])
	{
		return Backtrack(write_obj, t + 1);
	}
	// 该位置为空，则尝试所有的数
	else
	{
		bool resultFlag = true;
		// 尝试所有的数
		for (int i = 1; i < DIM + 1; i++)
		{
			board[x][y] = i;
			// 是否有重复
			if (CorrectPlace(x, y))
			{
				resultFlag = resultFlag && Backtrack(write_obj, t + 1);
			}
		}
		board[x][y] = 0;
		return resultFlag;
	}
	return false;
}