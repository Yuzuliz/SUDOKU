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

	reverse(arr, 0, arr_num - k - 1);
	reverse(arr, arr_num - k, arr_num - 1);
	reverse(arr, 0, arr_num - 1);
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

void SUDOKU::Initial(string input,string output)
{
	outputPath = output;
	//文件路径，输入参数，
	cout << "请输入初始形态：" << endl;
	string temp;
	for (int i = 0; i < 9; i++)
	{
		cin >> temp;
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = temp[j] - '0';
		}
	}
}

void SUDOKU::Shift() {
	move_left(board[1], 3, DIM);
	move_left(board[2], 6, DIM);
	move_left(board[3], 1, DIM);
	move_left(board[4], 4, DIM);
	move_left(board[5], 7, DIM);
	move_left(board[6], 2, DIM);
	move_left(board[7], 5, DIM);
	move_left(board[8], 8, DIM);
}

void SUDOKU::Display(string ps)
{
	ofstream out(outputPath, ios::out|ios::app);
	if (!out.is_open())
	{
		cout << "无法写出结果，请稍后再试！" << endl;
		return;
	}
	out << ps << endl;
	string result = "",temp;
	bool is_result = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j])
			{
				out << board[i][j] << ' ';
			}
			else
			{
				is_result = false;
				out << "$ ";
			}

		}
		out << endl;
	}
	out << "-------------------------\n";
	if (is_result)
	{
		for (int i = 0; i < 19; i++)
		{
			Shift();
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					out << board[i][j] << ' ';
				}
				out << endl;
			}
			out << "-------------------------\n";
		}
	}
	//out << result << endl;

	out.close();
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