#include "common.h"
#include "SUDOKU.h"
#include "File_Operation.h"
#include "opt.h"

int board[DIM][DIM] = { {0} };
string outputPath = "sudoku.txt";

int main(int argc,char* argv[])
{
	opt my_opt;
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