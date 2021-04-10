#include "common.h"
#include "SUDOKU.h"
#include "File_Operation.h"
#include "opt.h"

int board[DIM][DIM] = { {0} };
const string dir = "txtFiles";
const string Output_Path = dir + "sudoku.txt";
const string basic_path = dir + "basic_end.txt";
const string gen_path_end = dir + "end.txt";
const string gen_path_start = dir + "start.txt";
const char* optstring = "c:s:n:m:r:u"; // 设置短参数类型及是否需要参数


bool mk_txt_dir()
{
	//判断文件夹是否存在，不存在则创建
	if (_access(dir.c_str(), 0) == -1)
	{
		if (_mkdir(dir.c_str()) == -1)
			return 0;
	}
	return 1;
}

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

	if (!mk_txt_dir())
	{
		cout << "文件夹生成失败，请查看" << endl;
		return 0;
	}

	//输入错误字符检查，少输、多输检查，行列块重复检查

	my_opt.do_opt();  // 根据参数进行相应操作

	return 0;
}