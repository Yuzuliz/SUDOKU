#include "common.h"
#include "SUDOKU.h"
#include "File_Operation.h"
#include "opt.h"

int board[DIM][DIM] = { {0} };
string Output_Path = "sudoku.txt";
const char* optstring = "c:s:n:m:r:u"; // 设置短参数类型及是否需要参数

int main(int argc,char* argv[])
{
	//输入错误字符检查，少输、多输检查，行列块重复检查
	
	opt my_opt;
	// 参数解析
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