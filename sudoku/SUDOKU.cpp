// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#include "SUDOKU.h"

string align_string(string a) {
    if (a.size() != 9) a = "348276519";
    int shift[DIM - 1] = { 3, 6, 1, 4, 7, 2, 5, 8 };
    int index[DIM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    string result = "";
    for (int i = 0; i < DIM; i++) {
        result = result + a[index[i]] + ' ';
    }
    result += "\n";
    int cur_pos;
    for (int line = 1; line < DIM; line++) {
        cur_pos = shift[line - 1];
        for (int j = 0; j < DIM; j++, cur_pos++) {
            cur_pos = (cur_pos == DIM) ? 0 : cur_pos;
            result = result + a[index[cur_pos]] + ' ';
        }
        result += "\n";
    }
    result += "\n";
    return result;
}

string gen_first_line() {
    int diff[DIM] = { 0 }, index, j = 0;
    char c;
    string first_line = "";
    while (j < DIM) {
        index = rand() % DIM;
        if (diff[index]) {
            continue;
        }
        c = index + 1 + '0';
        first_line = first_line + c;
        diff[index] = 1;
        j++;
    }
    return first_line;
}

bool set_blanks(Write_File* write_out, int blanks) {
    /*srand((unsigned)time(NULL));*/
    if (blanks > 64 || blanks <= 0) return 0;
    int ran_i, ran_j;
    if (blanks >= 18) {
        // 2 blanks each row
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < 2; j++) {
                ran_j = rand() % DIM;
                if (write_out->board[i][ran_j] == '$') {
                    j--;
                    continue;
                }
                write_out->board[i][ran_j] = '$';
            }
        }
        blanks -= 18;
    }
    // Random position
    int k = 0;
    while (k < blanks) {
        ran_i = rand() % DIM;
        ran_j = rand() % DIM;
        if (write_out->board[ran_i][ran_j] == '$')
            continue;
        write_out->board[ran_i][ran_j] = '$';
        k++;
    }
    return 1;
}

bool SUDOKU::CorrectPlace(int x, int y) {
    if (x < 0 || x >= DIM || y < 0 || y >= DIM) {
        cout << "ERROR PLACE!" << endl;
        return false;
    }
    int side = sqrt(DIM);
    int up = x / side * side;
    int down = up + side;
    int left = y / side * side;
    int right = left + side;
    // Empty pos is valid
    if (board[x][y] == 0) {
        return true;
    }
    // Search for the row
    for (int i = 0; i < DIM; i++) {
        if (board[x][y] == board[i][y] && x != i) {
            return false;
        }
    }
    // Search for the col
    for (int i = 0; i < DIM; i++) {
        if (board[x][y] == board[x][i] && y != i) {
            return false;
        }
    }
    // Search for the 9*9
    for (int i = up; i < down; i++) {
        for (int j = left; j < right; j++) {
            if (board[x][y] == board[i][j]) {
                if (x != i || y != j) {
                    return false;
                }
            }
        }
    }
    return true;
}

void SUDOKU::Display(Write_File *write_obj, string ps) {
    string result;
    stringstream sstream;
    sstream << ps << '\n';
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (board[i][j]) {
                sstream << board[i][j] << ' ';
            } else {
                sstream << "$ ";
            }
        }
        sstream << endl;
    }
    sstream << "-------------------------\n";
    result = sstream.str();
    write_obj->write_data(result);
}

int SUDOKU::Backtrack(Write_File* write_obj, int t, bool write_out, bool distinct) {
    if (t < 0 || t > DIM * DIM) {
        cout << "ERROR POSITION!" << endl;
        return 0;
    }
    int result_num = 0;
    // One correct result
    if (t == DIM * DIM) {
        if(write_out)
            Display(write_obj, "Final board: ");
        return 1;
    }
    int x = t / DIM, y = t % DIM;
    // Get to the next one
    if (board[x][y]) {
        return Backtrack(write_obj, t + 1, write_out, distinct);
    } else {
        // Empty point. Test for all the values
        for (int i = 1; i < DIM + 1; i++) {
            board[x][y] = i;
            if (CorrectPlace(x, y)) {
                result_num += Backtrack(write_obj, t + 1, write_out, distinct);
                if (distinct && result_num > 1) return result_num;
            }
        }
        board[x][y] = 0;
        return result_num;
    }
}

bool SUDOKU::EndGen(int end_boards, Write_File* write_out) {
    if (end_boards <= 0 || end_boards > 1000000) return false;
    string first_line;
    srand((unsigned)time(NULL));
    for (int i = 0; i < end_boards; i++) {
        first_line = gen_first_line();
        write_out->write_data(align_string(first_line));
    }
    return true;
}

bool SUDOKU::StartGen(int start_boards, Write_File* write_out, int blanks_min, int blanks_max, bool distinct) {
    if (start_boards <= 0 || start_boards > 1000000) return false;
    if (blanks_min < 1 || blanks_max > 64 || blanks_max < blanks_min) {
        return false;
    }
    int cur_pos;
    int boards_number = 0;
    int shift[DIM - 1] = { 3, 6, 1, 4, 7, 2, 5, 8 };
    int index[DIM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    /*srand((unsigned)time(NULL));*/
    while (boards_number < start_boards) {
        int blanks = blanks_min + rand() % (blanks_max - blanks_min + 1);

        // Get the random first row
        string first_line = gen_first_line();
        for (int i = 0; i < DIM; i++) {
            write_out->board[0][i] = first_line[i];
        }

        // Shift the first row
        for (int line = 1; line < DIM; line++) {
            cur_pos = shift[line - 1];
            for (int j = 0; j < DIM; j++, cur_pos++) {
                cur_pos = (cur_pos == DIM) ? 0 : cur_pos;
                write_out->board[line][j] = write_out->board[0][index[cur_pos]];
            }
        }

        // Set blanks
        if (!set_blanks(write_out, blanks)) {
            cout << "error occured while generating blanks" << endl;
            return 0;
        }

        if (!change_char_2_int(write_out->board, board)) {
            cout << "error occured while changing char board to int board" << endl;
            return 0;
        }

        // Check if the answer is distinct
        if (distinct) {
            int result_num = Backtrack(write_out, 0, 0, distinct);
            if (result_num > 1) {
                continue;
            }
        }

        // Output
        write_out->write_data();
        write_out->write_data("\n");
        boards_number++;
    }
    return true;
}
