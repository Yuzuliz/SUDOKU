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
		cout << "参数错误" << endl;
		return 0;
	}
	cout << "参数解析结束" << endl;

	//输入错误字符检查，少输、多输检查，行列块重复检查
	string inputPath = "test.txt";

	my_opt.do_opt();
	
	return 0;
}