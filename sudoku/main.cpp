#include "getopt.h"                // ����ͷ�ļ�
#pragma comment(lib, "getopt.lib")   // ���ؾ�̬���ļ���Windows��

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

// �̲������԰���
void testGetOpt(int argc, char* argv[]) {
	int opt;  // getopt() �ķ���ֵ
	const char* optstring = "a:b:c:d"; // ���ö̲������ͼ��Ƿ���Ҫ����

	while ((opt = getopt(argc, argv, optstring)) != -1) {
		printf("opt = %c\n", opt);  // ����������༴ -a -b -c -d
		printf("optarg = %s\n", optarg); // ��������
		printf("optind = %d\n", optind); // ��һ����������±�ֵ
		printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // ��������
	}
}

int main(int argc,char* argv[])
{
	testGetOpt(argc, argv);
	cout << "������������" << endl;

	//��������ַ���飬���䡢�����飬���п��ظ����
	SUDOKU sudoku;
	string inputPath = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\test.txt";
	string outputPath = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\sudoku.txt";
	sudoku.Initial(inputPath,outputPath);
	sudoku.Display("��ǰ״̬��" );
	if (!sudoku.Backtrack())
	{
		cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
	}
	else
	{
		cout << "����ɹ�����鿴" << outputPath << endl;
	}
	getchar();
	
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