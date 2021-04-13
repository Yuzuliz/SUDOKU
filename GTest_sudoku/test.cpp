#include "pch.h"
int board[DIM][DIM] = { {0} };
const string dir = "txtFiles";
const string Output_Path = dir + "/sudoku.txt";
const string gen_path_end = dir + "/end.txt";
const string gen_path_start = dir + "/start.txt";
const string distinct_result = dir + "/distinct.txt";
const char* optstring = "c:s:n:m:r:u";  // short optstring type

// 测试样例
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

/* 文件测试 */
// 文件打开测试
TEST(FileTest, FileOpenTest) {
	// Write_File write_obj("");
	ASSERT_ANY_THROW(Write_File write_obj_test(""));
	ASSERT_ANY_THROW(Write_File write_false_test("txtFiles/test/permission_denied.txt"));
	ASSERT_ANY_THROW(Read_File Read_obj_test(""));
}

// 文件写测试
TEST(FileTest, FileWriteTest) {
	ifstream check_content1;
	Write_File write_board_test("txtFiles/test/test_board.txt");
	ASSERT_EQ(write_board_test.write_data(), 1);
	check_content1.open("txtFiles/test/test_board.txt", ios::in);
	check_content1.seekg(0, ios::end);
	ASSERT_EQ(check_content1.tellg(), 180);
	check_content1.close();

	Write_File write_string_test("txtFiles/test/test_string.txt");
	ASSERT_EQ(write_string_test.write_data("this is a test string.\n"), 1);
}

// 文件读测试
TEST(FileTest, FileReadTest) {
	Write_File write_obj("txtFiles/test/test_read.txt");
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			write_obj.board[i][j] = (i + 1 + j + 1) % DIM + '0';
		}
	}
	ASSERT_EQ(write_obj.write_data(), 1);

	Read_File read_obj("txtFiles/test/test_read.txt");
	ASSERT_EQ(read_obj.read_data(), 1);
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			ASSERT_EQ((i + 1 + j + 1) % DIM + '0', read_obj.board[i][j]);
		}
	}
	ASSERT_EQ(read_obj.read_eof(), 0);
	ASSERT_EQ(read_obj.read_data(), 0);
	ASSERT_EQ(read_obj.read_eof(), 1);
}

// char型board转int型board测试
TEST(FileTest, CharIntBoardTest) {
	char test_board_char[DIM][DIM];
	int test_board_int[DIM][DIM];
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			test_board_char[i][j] = (i + 1 + j + 1) % DIM + '0';
	ASSERT_EQ(change_char_2_int(test_board_char, test_board_int), 1);
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			ASSERT_EQ(test_board_int[i][j], (i + 1 + j + 1) % DIM);
}

/* SUDOKU测试 */
// 测试align_string()函数
TEST(SUDOKUTest, AlignStringTest) {
	string test_string = "123456789";
	string result = "1 2 3 4 5 6 7 8 9 \n\
4 5 6 7 8 9 1 2 3 \n\
7 8 9 1 2 3 4 5 6 \n\
2 3 4 5 6 7 8 9 1 \n\
5 6 7 8 9 1 2 3 4 \n\
8 9 1 2 3 4 5 6 7 \n\
3 4 5 6 7 8 9 1 2 \n\
6 7 8 9 1 2 3 4 5 \n\
9 1 2 3 4 5 6 7 8 \n\n";
	ASSERT_EQ(result, align_string(test_string));
	result = "3 4 8 2 7 6 5 1 9 \n2 7 6 5 1 9 3 4 8 \n5 1 9 3 4 8 2 7 6 \n4 8 2 7 6 5 1 9 3 \n\
7 6 5 1 9 3 4 8 2 \n1 9 3 4 8 2 7 6 5 \n8 2 7 6 5 1 9 3 4 \n6 5 1 9 3 4 8 2 7 \n9 3 4 8 2 7 6 5 1 \n\n";
	ASSERT_EQ(result, align_string("123"));
}

// 测试gen_first_line()函数
TEST(SUDOKUTest, GenFirstLineTest) {
	srand((unsigned)time(NULL));
	bool diff[DIM] = { 0 };
	string result = gen_first_line();
	for (int i = 0; i < DIM; i++) {
		ASSERT_EQ(diff[result[i] - '0' - 1], 0);
		diff[result[i] - '0' - 1] = 1;
	}
}

// 测试set_blanks()函数
TEST(SUDOKUTest, SetBlanksTest) {
	srand((unsigned)time(NULL));
	Write_File write_obj("txtFiles/test/test_blanks.txt");
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			write_obj.board[i][j] = (i + j + 2) % DIM + '0';

	ASSERT_EQ(set_blanks(&write_obj, 10), 1);
	int blanks = 0;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (write_obj.board[i][j] == '$') blanks++;
	ASSERT_EQ(blanks, 10);

	ASSERT_EQ(set_blanks(&write_obj, 70), 0);
	blanks = 0;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (write_obj.board[i][j] == '$') blanks++;
	ASSERT_EQ(blanks, 10);

	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			write_obj.board[i][j] = (i + j + 2) % DIM + '0';
	ASSERT_EQ(set_blanks(&write_obj, 25), 1);
	blanks = 0;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (write_obj.board[i][j] == '$') blanks++;
	ASSERT_EQ(blanks, 25);
}

// 测试EndGen()函数
TEST(SUDOKUTest, EndGenTest) {
	SUDOKU SUDOKU_obj;
	Write_File write_obj("txtFiles/test/test_end.txt");
	ASSERT_EQ(SUDOKU_obj.EndGen(0, &write_obj), 0);
	ASSERT_EQ(SUDOKU_obj.EndGen(10000000, &write_obj), 0);
	ASSERT_EQ(SUDOKU_obj.EndGen(10, &write_obj), 1);  // 直接打开文件查看生成是否正确
}

// 测试CorrectPlace()函数
TEST(SUDOKUTest, CorrectPlaceTest) {
	SUDOKU SUDOKU_obj;
	Read_File read_obj("txtFiles/test/test_cp.txt");
	ASSERT_EQ(read_obj.read_data(), 1);
	ASSERT_EQ(change_char_2_int(read_obj.board, board), 1);
	// 行
	board[0][0] = 2;
	ASSERT_EQ(SUDOKU_obj.CorrectPlace(0, 0), 0);
	// 列
	board[0][0] = 5;
	ASSERT_EQ(SUDOKU_obj.CorrectPlace(0, 0), 0);
	// 方块
	board[0][0] = 3;
	ASSERT_EQ(SUDOKU_obj.CorrectPlace(0, 0), 0);
	// 正确
	board[0][0] = 9;
	ASSERT_EQ(SUDOKU_obj.CorrectPlace(0, 0), 1);
}

// 测试Display()函数
TEST(SUDOKUTest, DisplayTest) {
	SUDOKU sudoku_obj;
	Write_File write_obj("txtFiles/test/test_Display.txt");
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			board[i][j] = (i + j + 2) % DIM + 1;
	sudoku_obj.Display(&write_obj, "test test: ");
}

// 测试Backtrack()函数
TEST(SUDOKUTest, BacktrackTest) {
	SUDOKU SUDOKU_obj;
	Read_File read_obj("txtFiles/test/test_bt.txt");
	ASSERT_EQ(read_obj.read_data(), 1);
	ASSERT_EQ(change_char_2_int(read_obj.board, board), 1);
	Write_File write_obj("txtFiles/test/test_bt.txt");
	ASSERT_EQ(SUDOKU_obj.Backtrack(&write_obj, -1, 0), 0);
	ASSERT_EQ(SUDOKU_obj.Backtrack(&write_obj, 100, 0), 0);
	ASSERT_EQ(SUDOKU_obj.Backtrack(&write_obj, 0, 0), 1);
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			write_obj.board[i][j] = read_obj.board[i][j];
	write_obj.write_data();
}

// 测试StartGen()函数
TEST(SUDOKUTest, StartGenTest) {
	SUDOKU SUDOKU_obj;
	Write_File write_obj("txtFiles/test/test_StartGen.txt");
	ASSERT_EQ(SUDOKU_obj.StartGen(0, &write_obj), 0);
	ASSERT_EQ(SUDOKU_obj.StartGen(10000000, &write_obj), 0);
	ASSERT_EQ(SUDOKU_obj.StartGen(1, &write_obj, 0), 0);
	ASSERT_EQ(SUDOKU_obj.StartGen(1, &write_obj, 20, 100), 0);
	ASSERT_EQ(SUDOKU_obj.StartGen(1, &write_obj, 20, 10), 0);
	ASSERT_EQ(SUDOKU_obj.StartGen(1, &write_obj, 10, 20), 1);
	ASSERT_EQ(SUDOKU_obj.StartGen(1, &write_obj, 30, 60, 1), 1);
}

/* opt测试 */
// 测试get_range()函数
TEST(optTest, GetRangeTest) {
	int min, max;
	ASSERT_EQ(get_range("15~", &min, &max), 0);
	ASSERT_EQ(get_range("15", &min, &max), 0);
	ASSERT_EQ(get_range("~15", &min, &max), 0);
	ASSERT_EQ(get_range("10~20", &min, &max), 1);
	ASSERT_EQ(max, 20);
	ASSERT_EQ(min, 10);
}

// 测试get_n_arg()函数
TEST(optTest, GetNArgTest) {
	opt opt_obj;
	int hole_min, hole_max;
	bool distinct = 0;
	opt_obj.opt_type = GEN_BOARD;
	opt_obj.opt_type_arg = "3";

	opt_obj.opt_append = 5;
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 0);

	opt_obj.opt_append = Difficulty;
	opt_obj.opt_append_arg = "0";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 0);
	opt_obj.opt_append_arg = "4";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 0);
	opt_obj.opt_append_arg = "1";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 1);
	ASSERT_EQ(hole_min, 10);
	ASSERT_EQ(hole_max, 20);
	opt_obj.opt_append_arg = "2";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 1);
	ASSERT_EQ(hole_min, 30);
	ASSERT_EQ(hole_max, 40);
	opt_obj.opt_append_arg = "3";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 1);
	ASSERT_EQ(hole_min, 50);
	ASSERT_EQ(hole_max, 60);

	opt_obj.opt_append = HoleNumbers;
	opt_obj.opt_append_arg = "1";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 0);
	opt_obj.opt_append_arg = "20~30";
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 1);
	ASSERT_EQ(hole_min, 20);
	ASSERT_EQ(hole_max, 30);

	opt_obj.opt_append = OnlySolution;
	ASSERT_EQ(opt_obj.get_n_arg(hole_min, hole_max, distinct), 1);
	ASSERT_EQ(distinct, 1);
}

// 测试get_opt()函数
TEST(optTest, GetOptTest) {
	opt opt_obj1;
	int argc = 3;
	char* argv1[] = { "sudoku.exe", "-c", "3"};
	ASSERT_EQ(opt_obj1.get_opt(argc, argv1), 1);
	ASSERT_EQ(opt_obj1.opt_type, END_BOARD);
	ASSERT_EQ(opt_obj1.opt_type_arg, "3");

	optind = 0;
	opt opt_obj2;
	argc = 3;
	char* argv2[] = { "sudoku.exe", "-s", "txtFiles/start.txt"};
	ASSERT_EQ(opt_obj2.get_opt(argc, argv2), 1);
	ASSERT_EQ(opt_obj2.opt_type, SOLVE_BOARD);
	ASSERT_EQ(opt_obj2.opt_type_arg, "txtFiles/start.txt");

	optind = 0;
	opt opt_obj3;
	argc = 5;
	char* argv3[] = { "sudoku.exe", "-n", "3", "-m", "2"};
	ASSERT_EQ(opt_obj3.get_opt(argc, argv3), 1);
	ASSERT_EQ(opt_obj3.opt_type, GEN_BOARD);
	ASSERT_EQ(opt_obj3.opt_type_arg, "3");
	ASSERT_EQ(opt_obj3.opt_append, Difficulty);
	ASSERT_EQ(opt_obj3.opt_append_arg, "2");

	optind = 0;
	opt opt_obj4;
	argc = 5;
	char* argv4[] = { "sudoku.exe", "-n", "3", "-r", "20~50" };
	ASSERT_EQ(opt_obj4.get_opt(argc, argv4), 1);
	ASSERT_EQ(opt_obj4.opt_type, GEN_BOARD);
	ASSERT_EQ(opt_obj4.opt_type_arg, "3");
	ASSERT_EQ(opt_obj4.opt_append, HoleNumbers);
	ASSERT_EQ(opt_obj4.opt_append_arg, "20~50");

	optind = 0;
	opt opt_obj5;
	argc = 4;
	char* argv5[] = { "sudoku.exe", "-n", "3", "-u" };
	ASSERT_EQ(opt_obj5.get_opt(argc, argv5), 1);
	ASSERT_EQ(opt_obj5.opt_type, GEN_BOARD);
	ASSERT_EQ(opt_obj5.opt_type_arg, "3");
	ASSERT_EQ(opt_obj5.opt_append, OnlySolution);

	optind = 0;
	opt opt_obj6;
	argc = 2;
	char* argv6[] = { "sudoku.exe", "-u" };
	ASSERT_EQ(opt_obj6.get_opt(argc, argv6), 0);

	optind = 0;
	opt opt_obj7;
	argc = 4;
	char* argv7[] = { "sudoku.exe", "-c", "3", "-u" };
	ASSERT_EQ(opt_obj7.get_opt(argc, argv7), 0);

	optind = 0;
	opt opt_obj8;
	argc = 5;
	char* argv8[] = { "sudoku.exe", "-c", "3", "-n", "4" };
	ASSERT_EQ(opt_obj8.get_opt(argc, argv8), 0);

	optind = 0;
	opt opt_obj9;
	argc = 5;
	char* argv9[] = { "sudoku.exe", "-n", "3", "-c", "4" };
	ASSERT_EQ(opt_obj9.get_opt(argc, argv9), 0);

	optind = 0;
	opt opt_obj10;
	argc = 5;
	char* argv10[] = { "sudoku.exe", "-n", "3", "-s", "txtFiles/start.txt" };
	ASSERT_EQ(opt_obj10.get_opt(argc, argv10), 0);

	optind = 0;
	opt opt_obj11;
	argc = 5;
	char* argv11[] = { "sudoku.exe", "-m", "3", "-r", "10" };
	ASSERT_EQ(opt_obj11.get_opt(argc, argv11), 0);

	optind = 0;
	opt opt_obj12;
	argc = 5;
	char* argv12[] = { "sudoku.exe", "-r", "3", "-m", "10" };
	ASSERT_EQ(opt_obj12.get_opt(argc, argv12), 0);

	optind = 0;
	opt opt_obj13;
	argc = 4;
	char* argv13[] = { "sudoku.exe", "-r", "3", "-u"};
	ASSERT_EQ(opt_obj13.get_opt(argc, argv13), 0);
}

// 测试do_solve_board()函数
TEST(optTest, DoSolveBoardTest) {
	opt opt_obj;
	opt_obj.opt_type = SOLVE_BOARD;
	opt_obj.opt_type_arg = "txtFiles/start.txt";
	ASSERT_EQ(opt_obj.do_solve_board(), 1);
	opt_obj.opt_type_arg = "txtFiles/no_exist.txt";
	ASSERT_EQ(opt_obj.do_solve_board(), 0);
}

// 测试do_end_board()函数
TEST(optTest, DoEndBoardTest) {
	opt opt_obj;
	opt_obj.opt_type = END_BOARD;
	ASSERT_EQ(opt_obj.do_end_board(), 0);
	opt_obj.opt_type_arg = "3";
	ASSERT_EQ(opt_obj.do_end_board(), 1);
}

// 测试do_gen_board()函数
TEST(optTest, DoGenBoard) {
	opt opt_obj;
	opt_obj.opt_type = GEN_BOARD;
	ASSERT_EQ(opt_obj.do_gen_board(), 0);
	opt_obj.opt_type_arg = "3";

	opt_obj.opt_append = Difficulty;
	opt_obj.opt_append_arg = "1";
	ASSERT_EQ(opt_obj.do_gen_board(), 1);
	opt_obj.opt_append = HoleNumbers;
	opt_obj.opt_append_arg = "5~10";
	ASSERT_EQ(opt_obj.do_gen_board(), 1);
	opt_obj.opt_append = OnlySolution;
	ASSERT_EQ(opt_obj.do_gen_board(), 1);
}

// 测试do_opt()函数
TEST(optTest, DoOptTest) {
	opt opt_obj;
	opt_obj.opt_type = 10;
	ASSERT_EQ(opt_obj.do_opt(), 0);

	opt_obj.opt_type = END_BOARD;
	ASSERT_EQ(opt_obj.do_opt(), 0);

	opt_obj.opt_type = GEN_BOARD;
	opt_obj.opt_append = Difficulty;
	opt_obj.opt_append_arg = "1";
	ASSERT_EQ(opt_obj.do_opt(), 0);
	opt_obj.opt_append = HoleNumbers;
	opt_obj.opt_append_arg = "5~10";
	ASSERT_EQ(opt_obj.do_opt(), 0);
	opt_obj.opt_append = OnlySolution;
	ASSERT_EQ(opt_obj.do_opt(), 0);

	opt_obj.opt_type = SOLVE_BOARD;
	ASSERT_EQ(opt_obj.do_opt(), 0);

	opt_obj.opt_type_arg = "3";

	opt_obj.opt_type = END_BOARD;
	ASSERT_EQ(opt_obj.do_opt(), 1);

	opt_obj.opt_type = GEN_BOARD;
	opt_obj.opt_append = Difficulty;
	opt_obj.opt_append_arg = "1";
	ASSERT_EQ(opt_obj.do_opt(), 1);
	opt_obj.opt_append = HoleNumbers;
	opt_obj.opt_append_arg = "5~10";
	ASSERT_EQ(opt_obj.do_opt(), 1);
	opt_obj.opt_append = OnlySolution;
	ASSERT_EQ(opt_obj.do_opt(), 1);

	opt_obj.opt_type = SOLVE_BOARD;
	opt_obj.opt_type_arg = "txtFiles/start.txt";
	ASSERT_EQ(opt_obj.do_opt(), 1);
}


// 测试生成唯一解
TEST(optTest, OnlySolutionTest) {
	opt opt_obj;
	opt_obj.opt_type = GEN_BOARD;
	opt_obj.opt_type_arg = "20";
	opt_obj.opt_append = OnlySolution;
	ASSERT_EQ(opt_obj.do_opt(), 1);
	opt_obj.opt_type = SOLVE_BOARD;
	opt_obj.opt_type_arg = "txtFiles/start.txt";
	opt_obj.opt_append = 0;
	Write_File write_obj("txtFiles/test/test_onlysolution.txt");
	Read_File read_obj("txtFiles/start.txt");
	Read_File read_obj2("txtFiles/start.txt");
	SUDOKU sudoku;
	for (int i = 0; i < 20; i++)
	{
		ASSERT_EQ(read_obj.read_data(), 1);
		ASSERT_EQ(change_char_2_int(read_obj.board, board), 1);
		ASSERT_EQ(sudoku.Backtrack(&write_obj, 0, 0, 0), 1);
	}
}