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
	ASSERT_ANY_THROW(Write_File write_false_test("txtFiles/permission_denied.txt"));
	ASSERT_ANY_THROW(Read_File Read_obj_test(""));
}

// 文件写测试
TEST(FileTest, FileWriteTest) {
	ifstream check_content1;
	Write_File write_board_test("txtFiles/test_board.txt");
	ASSERT_EQ(write_board_test.write_data(), 1);
	check_content1.open("txtFiles/test_board.txt", ios::in);
	check_content1.seekg(0, ios::end);
	ASSERT_EQ(check_content1.tellg(), 180);
	check_content1.close();

	Write_File write_string_test("txtFiles/test_string.txt");
	ASSERT_EQ(write_string_test.write_data("this is a test string.\n"), 1);
}

// 文件读测试
TEST(FileTest, FileReadTest) {
	Write_File write_obj("txtFiles/test_read.txt");
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			write_obj.board[i][j] = (i + 1 + j + 1) % DIM + '0';
		}
	}
	ASSERT_EQ(write_obj.write_data(), 1);

	Read_File read_obj("txtFiles/test_read.txt");
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
	for (int i = 0; i < 0; i++)
		for (int j = 0; j < 0; j++)
			test_board_char[i][j] = (i + 1 + j + 1) % DIM + '0';
	ASSERT_EQ(change_char_2_int(test_board_char, test_board_int), 1);
	for (int i = 0; i < 0; i++)
		for (int j = 0; j < 0; j++)
			ASSERT_EQ(test_board_int[i][j], (i + 1 + j + 1) % DIM);
}

/* SUDOKU测试 */
TEST(SUDOKUTest, AlignStringTest) {
	string test_string = "348276519";
	string result = "348276519\n276519348\n519348276\n482765193\n765193482\n193482765\n827651934\n651934827\n934827651\n";
	//ASSERT_EQ(result, align_string(test_string));
	//cout << align_string("123");
}