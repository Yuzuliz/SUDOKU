#include "opt.h"
#include "File_Operation.h"
#include "SUDOKU.h"

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
	if (this->opt_append != 0 && this->opt_type != SOLVE_BOARD) return 0;
	if (this->opt_type == 0) return 0;
	return 1;
}

bool opt::do_solve_board()
{
	Read_File read_obj(this->opt_type_arg);
	SUDOKU sudoku(outputPath);
	while (!read_obj.read_eof())
	{
		if (!read_obj.read_data()) break;
		read_obj.show_board();
		cout << endl;
		change_char_2_int(read_obj.board, board);
		sudoku.Display("当前状态: ");
	}
}

bool opt::do_end_board()
{
	int board_numbers = atoi(this->opt_append_arg.c_str());
}

bool opt::do_gen_board()
{
	int board_numbers = atoi(this->opt_append_arg.c_str());
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