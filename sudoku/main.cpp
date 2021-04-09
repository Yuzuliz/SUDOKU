#include "getopt.h"                // 包含头文件
#pragma comment(lib, "getopt.lib")   // 加载静态库文件（Windows）

#include <stdlib.h>
#include <stdio.h>

#include "SUDOKU.h"

/*
int parseOptions(int argc, char** argv, int& imgWid, int& imgHei, int& imgCnt)
{
	int i = 0;
	if (argc == 1)
	{
		return -1;
	}
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-w") == 0)
		{
			imgWid = (int)atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-h") == 0)
		{
			imgHei = (int)atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			imgCnt = (int)atoi(argv[++i]);
		}

		else
			return -1;
	}

	return 0;
}*/

// 短参数测试案例
void testGetOpt(int argc, char* argv[]) {
	int opt;  // getopt() 的返回值
	const char* optstring = "a:b:c:d"; // 设置短参数类型及是否需要参数

	while ((opt = getopt(argc, argv, optstring)) != -1) {
		printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
		printf("optarg = %s\n", optarg); // 参数内容
		printf("optind = %d\n", optind); // 下一个被处理的下标值
		printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // 参数内容
	}
}

int main(int argc,char* argv[])
{
	testGetOpt(argc, argv);
	cout << "参数解析结束" << endl;

	//输入错误字符检查，少输、多输检查，行列块重复检查
	SUDOKU sudoku;
	string inputPath = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\test.txt";
	string outputPath = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\sudoku.txt";
	sudoku.Initial(inputPath,outputPath);
	sudoku.Display("当前状态：" );
	if (!sudoku.Backtrack())
	{
		cout << "运算失败，请检查输入是否合法！" << endl;
	}
	else
	{
		cout << "运算成功，请查看" << outputPath << endl;
	}
	getchar();
	
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