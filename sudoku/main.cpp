#include "common.h"
#include "SUDOKU.h"
#include "File_Operation.h"
#include "opt.h"

int board[DIM][DIM] = { {0} };
string Output_Path = "sudoku.txt";
const char* optstring = "c:s:n:m:r:u"; // ���ö̲������ͼ��Ƿ���Ҫ����

int main(int argc,char* argv[])
{
	//��������ַ���飬���䡢�����飬���п��ظ����
	
	opt my_opt;
	// ��������
	if (!my_opt.get_opt(argc, argv))
	{
		cout << "��������" << endl;
		return 0;
	}
	cout << "������������" << endl;

	//��������ַ���飬���䡢�����飬���п��ظ����
	string inputPath = "test.txt";

	my_opt.do_opt();	
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