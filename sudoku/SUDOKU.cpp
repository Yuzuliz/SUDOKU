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

string align_string(string a)
{
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
		result += "\n";
	} while (next_permutation(index, index + DIM));
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

bool SUDOKU::EndGen(int end_boards, Write_File *write_out)
{
	string result = "";
	string first_line;
	short int diff[DIM],index,j;
	char c;
	srand((unsigned)time(NULL));
	for (int i = 0; i < end_boards; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			diff[j] = 0;
		}
		first_line = "";
		j = 0;
		while (j < DIM)
		{
			index = rand() % DIM;
			if (diff[index])
			{
				continue;
			}
			c = index + 1 + '0';
			first_line = first_line + c;
			diff[index] = 1;
			j++;
		}
		/*for (int j = 0; j < DIM; j++)
		{
			c = (rand() % DIM + 1) + '0';
			first_line = first_line + c;
		}*/
		result = result + align_string(first_line);
	}
	/*
	string result = align_string(read_in->get_first_line(), end_boards);*/
	if (result == "")
	{
		return false;
	}
	write_out->write_data(result);
	return true;
}

bool SUDOKU::StartGen(int start_boards, Write_File* write_out, int blanks)
{
	if (blanks < 20 || blanks > 55)
	{
		return false;
	}
	int ran_i,ran_j,i,j,k=0,cur_pos,boards_number=0;
	int diff[DIM];
	string result="";
	char temp_board[DIM][DIM],c;
	int shift[DIM - 1] = { 3, 6, 1, 4, 7, 2, 5, 8 };
	int index[DIM] = { 0,1,2,3,4,5,6,7,8 };
	srand((unsigned)time(NULL));
	for (; boards_number < start_boards; boards_number++)
	{
		//生成终局
		for (int j = 0; j < DIM; j++)
		{
			diff[j] = 0;
		}
		j = 0;
		k = 0;
		while (j < DIM)
		{
			i = rand() % DIM;
			if (diff[i])
			{
				continue;
			}
			c = i + 1 + '0';
			temp_board[0][k++] = c;
			diff[i] = 1;
			j++;
		}

		for (int i = 0; i < DIM; i++)
			cout << temp_board[0][i] << " ";
		cout << endl << endl;

		//for (i = 0; i < DIM; i++)
		//	result = result + temp_board[0][i] + ' ';
		//result = result + '\n';

		for (int line = 1; line < DIM; line++)
		{
			cur_pos = shift[line - 1];
			for (int j = 0; j < DIM; j++, cur_pos++)
			{
				cur_pos = (cur_pos == DIM) ? 0 : cur_pos;
				temp_board[line][j] = temp_board[0][index[cur_pos]];
			}
		}
		/*for (i = 0; i < DIM; i++)
		{
			for (j = 0; j < DIM; j++)
			{
				result = result + temp_board[i][j] + ' ';
			}
			result = result + '\n';
		}
		result = result + "\n\n";*/

		//for (i = 0; i < DIM; i++)
		//{
		//	for (j = 0; j < DIM; j++)
		//	{
		//		cout << temp_board[i][j] << ' ';
		//	}
		//	cout << endl;
		//}
			
		//挖空
		for (i = 0; i < DIM; i++)
		{
			j = 0;
			while (j < 2)
			{
				ran_j = rand() % 9;
				if (temp_board[i][ran_j] == '$')
					continue;
				temp_board[i][ran_j] = '$';
				j++;
			}
		}
		k = 0;
		while (k < blanks - 18)
		{
			ran_i = rand() % 9;
			ran_j = rand() % 9;
			if (temp_board[ran_i][ran_j] == '$')
				continue;
			temp_board[ran_i][ran_j] = '$';
			k++;
		}
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				result = result + temp_board[i][j] + ' ';
			}
			result = result + '\n';
		}
		result = result + '\n';
	}
	write_out->write_data(result);
	/*string result = align_string(read_in->get_first_line(), 1);
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