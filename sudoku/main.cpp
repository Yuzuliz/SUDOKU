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
const char* optstring = "c:s:n:m:r:u"; // ���ö̲������ͼ��Ƿ���Ҫ����


bool mk_txt_dir()
{
	//�ж��ļ����Ƿ���ڣ��������򴴽�
	if (_access(dir.c_str(), 0) == -1)
	{
		if (_mkdir(dir.c_str()) == -1)
			return 0;
	}
	return 1;
}

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

	if (!mk_txt_dir())
	{
		cout << "�ļ�������ʧ�ܣ���鿴" << endl;
		return 0;
	}

	//��������ַ���飬���䡢�����飬���п��ظ����

	my_opt.do_opt();  // ���ݲ���������Ӧ����

	return 0;
}