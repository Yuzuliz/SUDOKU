#include "SUDOKU.h"


int main()
{
	

	//输入错误字符检查，少输、多输检查，行列块重复检查
	SUDOKU sudoku;
	sudoku.Initial();
	cout << "当前状态：" << endl;
	sudoku.Display();
	if (!sudoku.Backtrack())
	{
		cout << "运算失败，请检查输入是否合法！" << endl;
	}

	
	return 0;
}

/*if (backtrack())
{
	cout << "填充后形态为：" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}
else
{
	cout << "运算失败，请检查输入是否合法！" << endl;
}*/