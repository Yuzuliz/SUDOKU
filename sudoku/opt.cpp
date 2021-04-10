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
	try
	{
		Read_File read_obj(this->opt_type_arg);
		Write_File *write_obj = new Write_File(Output_Path);
		while (!read_obj.read_eof())
		{
			if (!read_obj.read_data()) break;
			read_obj.show_board();
			cout << endl;
			change_char_2_int(read_obj.board, board);
			this->sudoku->Display(write_obj, "��ǰ״̬: ");
			if (!sudoku->Backtrack(write_obj))
			{
				cout << "����ʧ�ܣ����������Ƿ�Ϸ���" << endl;
				delete write_obj;
				return 0;
			}
			else
			{
				cout << "����ɹ�����鿴" << Output_Path << endl;
			}
		}
		delete write_obj;
		return 1;
	}
	catch (string msg)
	{
		cerr << msg << endl;
		return 0;
	}
}

bool opt::do_end_board()
{
	int board_numbers = atoi(this->opt_type_arg.c_str());
	cout << board_numbers << endl;
	try
	{
		Read_File* read_obj = new Read_File(basic_path);
		read_obj->read_data();
		Write_File* write_obj = new Write_File(gen_path_end);
		if (!this->sudoku->EndGen(board_numbers, read_obj, write_obj))
		{
			cout << "�վ�����ʧ�ܣ���������ԣ�" << endl;
			delete read_obj;
			delete write_obj;
			return 0;
		}
		else
		{
			cout << "�վ����ɳɹ�����鿴" << gen_path_end << endl;
		}
		delete read_obj;
		delete write_obj;
		return 1;
	}
	catch (string msg)
	{
		cerr << msg << endl;
		return 0;
	}
}

bool opt::do_gen_board()
{
	int board_numbers = atoi(this->opt_type_arg.c_str());
	int hole_numbers = atoi(this->opt_append_arg.c_str());
	try
	{
		Read_File* read_obj = new Read_File(basic_path);
		Write_File* write_obj = new Write_File(gen_path_start);
		if (!this->sudoku->StartGen(board_numbers, read_obj, write_obj, hole_numbers))
		{
			cout << "��������ʧ�ܣ���������ԣ�" << endl;
			delete read_obj;
			delete write_obj;
			return 0;
		}
		else
		{
			cout << "�������ɳɹ�����鿴" << gen_path_start << endl;
		}
		delete read_obj;
		delete write_obj;
		return 1;
	}
	catch (string msg)
	{
		cerr << msg << endl;
		return 0;
	}
}

bool opt::do_opt()
{
	if (this->opt_type == SOLVE_BOARD)
	{
		if (!this->do_solve_board())
		{
			cout << "���ʧ�ܣ���鿴�����Ƿ���ȷ" << endl;
			return 0;
		}
	}
	else if (this->opt_type == END_BOARD)
	{
		if (!this->do_end_board())
		{
			cout << "�վ�����ʧ�ܣ���鿴�����Ƿ���ȷ" << endl;
			return 0;
		}
	}
	else if (this->opt_type == GEN_BOARD)
	{
		if (!this->do_gen_board())
		{
			cout << "��Ŀ����ʧ�ܣ���鿴�����Ƿ���ȷ" << endl;
			return 0;
		}
	}
	else
	{
		cout << "�����ڵ�״̬����鿴�����Ƿ���ȷ" << endl;
		return 0;
	}
	return 1;
}