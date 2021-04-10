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
////����kλ
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
		// ���ݵ�һ�д��ݺ������
		for (int line = 1; line < DIM; line++)
		{
			cur_pos = shift[line - 1];
			// ���Ƶ���һ��
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
		cout << "����λ�ô�������" << endl;
		return false;
	}
	int side = sqrt(DIM);
	int up = x / side * side;
	int down = up + side;
	int left = y / side * side;
	int right = left + side;
	// ������0������ǰ��Ϊ�գ������û���ظ�
	if (board[x][y] == 0)
	{
		return true;
	}
	// ��֤����û���ظ�
	for (int i = 0; i < DIM; i++)
	{
		if (board[x][y] == board[i][y] && x != i)
		{
			return false;
		}
	}
	// ��֤����û���ظ�
	for (int i = 0; i < DIM; i++)
	{
		if (board[x][y] == board[x][i] && y != i)
		{
			return false;
		}
	}
	// ��֤����û���ظ�
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

void SUDOKU::Display(string ps)
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
	try
	{
		Write_File write_obj(Output_Path);
		write_obj.write_data(result);
	}
	catch (string msg)
	{
		cerr << msg << endl;
	}
}

bool SUDOKU::EndGen(int end_boards, Read_File *read_in, Write_File *write_out)
{
	if (end_boards > 1000000 || end_boards < 1)
	{
		cout << "�վ��������ڳ�����ܷ�Χ��" << endl;
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

bool SUDOKU::Backtrack(int t)
{
	if (t < 1 || t > DIM * DIM)
	{
		cout << "���ݳ�������" << endl;
		return false;
	}
	// �Ѿ������������ϵ�����λ��
	if (t == DIM*DIM)
	{
		Display("�վ�״̬��");
		return true;
	}
	int x = t / DIM, y = t % DIM;
	// ������λ���ϱ�������ֵ���Ǿͷ�����һ��λ��
	if (board[x][y])
	{
		return Backtrack(t + 1);
	}
	// ��λ��Ϊ�գ��������е���
	else
	{
		bool resultFlag = true;
		// �������е���
		for (int i = 1; i < DIM + 1; i++)
		{
			board[x][y] = i;
			// �Ƿ����ظ�
			if (CorrectPlace(x, y))
			{
				resultFlag = resultFlag && Backtrack(t + 1);
			}
		}
		board[x][y] = 0;
		return resultFlag;
	}
	return false;
}