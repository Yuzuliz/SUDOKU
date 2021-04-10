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
		printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
		printf("optarg = %s\n", optarg); // 参数内容
		printf("optind = %d\n", optind); // 下一个被处理的下标值
		printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // 参数内容
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
			this->sudoku->Display(write_obj, "当前状态: ");
			if (!sudoku->Backtrack(write_obj))
			{
				cout << "运算失败，请检查输入是否合法！" << endl;
				delete write_obj;
				return 0;
			}
			else
			{
				cout << "运算成功，请查看" << Output_Path << endl;
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
			cout << "终局生成失败，请检查后重试！" << endl;
			delete read_obj;
			delete write_obj;
			return 0;
		}
		else
		{
			cout << "终局生成成功，请查看" << gen_path_end << endl;
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
			cout << "初局生成失败，请检查后重试！" << endl;
			delete read_obj;
			delete write_obj;
			return 0;
		}
		else
		{
			cout << "初局生成成功，请查看" << gen_path_start << endl;
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
			cout << "解局失败，请查看操作是否正确" << endl;
			return 0;
		}
	}
	else if (this->opt_type == END_BOARD)
	{
		if (!this->do_end_board())
		{
			cout << "终局生成失败，请查看操作是否正确" << endl;
			return 0;
		}
	}
	else if (this->opt_type == GEN_BOARD)
	{
		if (!this->do_gen_board())
		{
			cout << "题目生成失败，请查看操作是否正确" << endl;
			return 0;
		}
	}
	else
	{
		cout << "不存在的状态，请查看操作是否正确" << endl;
		return 0;
	}
	return 1;
}