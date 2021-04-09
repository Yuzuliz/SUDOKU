#include "common.h"
#include "SUDOKU.h"
#include "File_Operation.h"

int board[DIM][DIM] = { {0} };

enum { END_BOARD, SOLVE_BOARD, GEN_BOARD };

void change_char_2_int(char board1[DIM][DIM], int board2[DIM][DIM])
{
	for(int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
		{
			board2[i][j] = board1[i][j] - '0';
		}
}

// 短参数测试案例
void testGetOpt(int argc, char* argv[],int &mode,int &attr1) {
	int opt;  // getopt() 的返回值
	const char* optstring = "c:m:n:r:s:u"; // 设置短参数类型及是否需要参数

	while ((opt = getopt(argc, argv, optstring)) != -1) {
		printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
		printf("optarg = %s\n", optarg); // 参数内容
		printf("optind = %d\n", optind); // 下一个被处理的下标值
		printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // 参数内容
	}
}

int main(int argc,char* argv[])
{
	int BOARD_MODE, ATTR1, SECOND_MODE, ATTR2;
	testGetOpt(argc, argv,BOARD_MODE,ATTR1);
	cout << "参数解析结束" << endl;

	//输入错误字符检查，少输、多输检查，行列块重复检查
	string dir = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\Debug\\txtFiles\\";
	string inputPath = dir + "test.txt";
	string outputPath = dir + "sudoku.txt";
	Read_File read_obj(inputPath);
	read_obj.read_data();
	read_obj.show_board();
	cout << endl;
	read_obj.read_data();
	read_obj.show_board();
	cout << endl;
	change_char_2_int(read_obj.board, board);

	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}

	SUDOKU sudoku(outputPath);
	sudoku.Display("当前状态：" );
	//if (!sudoku.Backtrack())
	//{
	//	cout << "运算失败，请检查输入是否合法！" << endl;
	//}
	//else
	//{
	//	cout << "运算成功，请查看" << outputPath << endl;
	//}
	//getchar();
	
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