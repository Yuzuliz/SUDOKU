#include "SUDOKU.h"


int main()
{
	

	//��������ַ���飬���䡢�����飬���п��ظ����
	SUDOKU sudoku;
	sudoku.Initial();
	cout << "��ǰ״̬��" << endl;
	sudoku.Display();
	if (!sudoku.Backtrack())
	{
		cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
	}

	
	return 0;
}

/*if (backtrack())
{
	cout << "������̬Ϊ��" << endl;
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
	cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
}*/