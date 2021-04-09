#pragma once
#include <iostream>
using namespace std;


class SUDOKU
{
	int board[9][9];
public:
	bool CorrectPlace(int x, int y)
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

	void Initial()
	{
		cout << "ÇëÊäÈë³õÊ¼ÐÎÌ¬£º" << endl;
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

	void Display()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << board[i][j] << ' ';
			}
			cout << endl;
		}
	}



	bool Backtrack(int t = 0)
	{
		if (t == 81)
		{
			cout << "ÖÕ¾Ö×´Ì¬£º" << endl;
			Display();
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
};