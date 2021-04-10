#pragma once
#include "SUDOKU.h"

void reverse(int* arr, int begin, int end)
{
	for (; begin < end; begin++, end--)
	{
		int temp = arr[begin];
		arr[begin] = arr[end];
		arr[end] = temp;
	}

}

//左移k位
void move_left(int* arr, int k, int arr_num)
{
	k = k % arr_num;
	reverse(arr, 0, k - 1);
	reverse(arr, k, arr_num - 1);
	/*reverse(arr, 0, arr_num - k - 1);
	reverse(arr, arr_num - k, arr_num - 1);*/
	reverse(arr, 0, arr_num - 1);
}

string align(string a,int N)
{
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
		for (int line = 1; line < DIM; line++)
		{
			cur_pos = shift[line - 1];
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
	/*
	int k = 1;
	short int shift[8] = { 3, 6, 1, 4, 7, 2, 5, 8 };
	stringstream sstream;
	do {
		for (int i = 0; i < DIM; i++)
			sstream << a[i] << ' ';
		sstream << "\n";

		for (int line = 1; line < DIM; line++)
		{
			for (int cur_pos = shift[line-1], j = 0; j < DIM; j++, cur_pos++)
			{
				if (cur_pos >= DIM)
				{
					cur_pos %= DIM;
				}
				sstream << a[cur_pos] << ' ';
			}
			sstream << "\n";
		}
		k++;
		sstream << "---->>><<<----\n";
	} while (next_permutation(a, a + DIM) && k < N);
	return sstream.str();
	*/
}

bool SUDOKU::CorrectPlace(int x, int y)
{
	int up = x / 3 * 3;
	int down = up + 3;
	int left = y / 3 * 3;
	int right = left + 3;
	if (board[x][y] == 0)
	{
		return true;
	}
	for (int i = 0; i < 9; i++)
	{
		if (board[x][y] == board[i][y] && x != i)
		{
			return false;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (board[x][y] == board[x][i] && y != i)
		{
			return false;
		}
	}
	for (int i = up; i < down; i++)
	{
		for (int j = left; j < right; j++)
		{
			if (board[x][y] == board[i][j])
			{
				if (x == i && y == j)
				{
					//Do nothing.
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}

void SUDOKU::Initial(string output)
{
	this->Output_Path = output;
	//文件路径，输入参数，
	/*cout << "请输入初始形态：" << endl;
	string temp;
	for (int i = 0; i < 9; i++)
	{
		cin >> temp;
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = temp[j] - '0';
		}
	}*/
}

void SUDOKU::Display(string ps)
{
	string result;
	stringstream sstream;
	sstream << ps << '\n';
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
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
	
	//out << result << endl;
	result = sstream.str();
	Write_File write_obj(Output_Path);
	// ofstream out(outputPath, ios::out|ios::app);
	//if (!out.is_open())
	//{
	//	cout << "无法写出结果，请稍后重试！" << endl;
	//	return;
	//}
	//out << result;
	//out.close();
	write_obj.write_data(result);
}

bool SUDOKU::EndGen(int end_boards, Read_File *read_in, Write_File *write_out)
{
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
	int ran_i,ran_j,i,j,k,boards;
	string result="";
	for (boards = 0; boards < start_boards; boards++)
	{
		read_in->read_data();
		for (i = 0; i < DIM; i++)
		{
			j = 0;
			while (j < 2)
			{
				ran_j = rand() % 9;
				if (read_in->board[i][ran_j] == '$')
					continue;
				read_in->board[i][ran_j] = '$';
				j++;
			}
		}
		k = 0;
		while (k < blanks - 18)
		{
			ran_i = rand() % 9;
			ran_j = rand() % 9;
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
	/*string result = align(read_in->get_first_line(), 1);
	string current_board[DIM];
	for (int i = 0; i < DIM; i++)
	{
		current_board[i] = "";
	}
	for (int i = 0; i < DIM; i++)
	{
		int k = 0;
		for (int j = 0; j < 2*DIM; j++)
		{
			if (result[2 * DIM * i + j] == ' ')
				continue;
			if (result[2 * DIM * i + j] == '\n')
				break;
			current_board[i] = current_board[i] + result[2 * DIM * i + j];
		}
	}
	for (int i = 0; i < DIM; i++)
	{
		cout << current_board[i] << endl;
	}
	if (result == "")
	{
		return false;
	}*/
	return true;
}

bool SUDOKU::Backtrack(int t)
{
	if (t == 81)
	{
		Display("终局状态：");
		return true;
	}
	int x = t / 9, y = t % 9;
	if (board[x][y])
	{
		return Backtrack(t + 1);
	}
	else
	{
		bool resultFlag = true;
		for (int i = 1; i < 10; i++)
		{
			board[x][y] = i;
			if (CorrectPlace(x, y))
			{
				resultFlag = resultFlag && Backtrack(t + 1);
			}
			board[x][y] = 0;
		}
		return resultFlag;
	}
	return false;
}