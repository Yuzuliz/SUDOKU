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