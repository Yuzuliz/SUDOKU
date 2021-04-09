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

// �̲������԰���
void testGetOpt(int argc, char* argv[],int &mode,int &attr1) {
	int opt;  // getopt() �ķ���ֵ
	const char* optstring = "c:m:n:r:s:u"; // ���ö̲������ͼ��Ƿ���Ҫ����

	while ((opt = getopt(argc, argv, optstring)) != -1) {
		printf("opt = %c\n", opt);  // ����������༴ -a -b -c -d
		printf("optarg = %s\n", optarg); // ��������
		printf("optind = %d\n", optind); // ��һ����������±�ֵ
		printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // ��������
	}
}

int main(int argc,char* argv[])
{
	int BOARD_MODE, ATTR1, SECOND_MODE, ATTR2;
	testGetOpt(argc, argv,BOARD_MODE,ATTR1);
	cout << "������������" << endl;

	//��������ַ���飬���䡢�����飬���п��ظ����
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
	sudoku.Display("��ǰ״̬��" );
	//if (!sudoku.Backtrack())
	//{
	//	cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
	//}
	//else
	//{
	//	cout << "����ɹ�����鿴" << outputPath << endl;
	//}
	//getchar();
	
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