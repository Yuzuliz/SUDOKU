#include "opt.h"
#include "File_Operation.h"
#include "SUDOKU.h"

opt::~opt()
{
	delete this->sudoku;
}

bool opt::get_opt(int argc, char* argv[]) {
	int opt;

	while ((opt = getopt(argc, argv, optstring)) != -1) {
		printf("opt = %c\n", opt);  // ����������༴ -a -b -c -d
		printf("optarg = %s\n", optarg); // ��������
		printf("optind = %d\n", optind); // ��һ����������±�ֵ
		printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // ��������
		switch (opt)
		{
		case 'c':
			if (this->opt_type != 0) return 0;
			this->opt_type = END_BOARD;
			this->opt_type_arg = optarg;
			break;
		case 's':
			cout << this->opt_type << endl;
			if (this->opt_type != 0) return 0;
			this->opt_type = SOLVE_BOARD;
			this->opt_type_arg = optarg;
			break;
		case 'n':
			if (this->opt_type != 0) return 0;
			this->opt_type = GEN_BOARD;
			this->opt_type_arg = optarg;
			break;
		case 'm':
			if (this->opt_append != 0) return 0;
			this->opt_append = Difficulty;
			this->opt_append_arg = optarg;
			break;
		case 'r':
			if (this->opt_append != 0) return 0;
			this->opt_append = HoleNumbers;
			this->opt_append_arg = optarg;
			break;
		case 'u':
			if (this->opt_append != 0) return 0;
			this->opt_append = OnlySolution;
			this->opt_append_arg = optarg;
			break;
		}
	}
	if (this->opt_append != 0 && this->opt_type != GEN_BOARD) return 0;
	if (this->opt_type == 0) return 0;
	return 1;
}

bool opt::do_solve_board()
{
	Read_File read_obj(this->opt_type_arg);
	while (!read_obj.read_eof())
	{
		if (!read_obj.read_data()) break;
		read_obj.show_board();
		cout << endl;
		change_char_2_int(read_obj.board, board);
		this->sudoku->Display("��ǰ״̬: ");
		if (!sudoku->Backtrack())
		{
			cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
			return 0;
		}
		else
		{
			cout << "����ɹ�����鿴" << Output_Path << endl;
		}
	}
	/*string dir = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\Debug\\txtFiles\\";
	string input_path = dir + "test_with_dollar.txt";
	string output_path = dir + "sudoku.txt";*/
	/*
	Read_File *read_obj = new Read_File(input_path);
	//Write_File* write_obj = new Write_File(output_path);

	SUDOKU sudoku(output_path);
	sudoku.Display("��ǰ״̬��" );
	if (!sudoku.Backtrack())
	{
		cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
	}
	else
	{
		cout << "����ɹ�����鿴" << output_path << endl;
	}
	*/
	return 1;
}

bool opt::do_end_board()
{
	int board_numbers = atoi(this->opt_type_arg.c_str());
	cout << board_numbers << endl;
	string dir = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\Debug\\txtFiles\\";
	string basic_path = dir + "basic_end.txt";
	string gen_path = dir + "end.txt";
	Read_File* read_obj = new Read_File(basic_path);
	read_obj->read_data();
	Write_File* write_obj = new Write_File(gen_path);
	if (!this->sudoku->EndGen(board_numbers, read_obj, write_obj))
	{
		cout << "�վ�����ʧ�ܣ���������ԣ�" << endl;
		return 0;
	}
	else
	{
		cout << "�վ����ɳɹ�����鿴" << gen_path << endl;
	}
	return 1;
}

bool opt::do_gen_board()
{
	int board_numbers = atoi(this->opt_type_arg.c_str());
	int hole_numbers = atoi(this->opt_append_arg.c_str());
	string dir = "D:\\CODES\\C++\\softwareEngineering\\sudoku\\Debug\\txtFiles\\";
	string basic_path = dir + "basic_end.txt";
	string gen_path = dir + "start.txt";
	Read_File* read_obj = new Read_File(basic_path);
	Write_File* write_obj = new Write_File(gen_path);
	if (!this->sudoku->StartGen(board_numbers, read_obj, write_obj, hole_numbers))
	{
		cout << "��������ʧ�ܣ���������ԣ�" << endl;
		return 0;
	}
	else
	{
		cout << "�������ɳɹ�����鿴" << gen_path << endl;
	}
	return 1;
}

bool opt::do_opt()
{
	if (this->opt_type == SOLVE_BOARD)
	{
		this->do_solve_board();
	}
	else if (this->opt_type == END_BOARD)
	{
		this->do_end_board();
	}
	else if (this->opt_type == GEN_BOARD)
	{
		this->do_gen_board();
	}
	else
	{
		return 0;
	}
	return 1;
}