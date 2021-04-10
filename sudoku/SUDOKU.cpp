// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#include <string>
#include "SUDOKU.h"

string align_string(string a) {
    int16 shift[DIM - 1] = { 3, 6, 1, 4, 7, 2, 5, 8 };
    int16 index[DIM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
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

int SUDOKU::Backtrack(Write_File* write_obj, int t) {
    if (t < 0 || t > DIM * DIM) {
        cout << "ERROR POSITION!" << endl;
        return 0;
    }
    // One correct result
    if (t == DIM * DIM) {
        Display(write_obj, "Final board: ");
        return 1;
    }
    int x = t / DIM, y = t % DIM;
    // Get to the next one
    if (board[x][y]) {
        return Backtrack(write_obj, t + 1);
    } else {
        // Empty point. Test for all the values
        int result_num = 0;
        for (int i = 1; i < DIM + 1; i++) {
            board[x][y] = i;
            if (CorrectPlace(x, y)) {
                result_num += Backtrack(write_obj, t + 1);
            }
        }
        board[x][y] = 0;
        return result_num;
    }
}

bool SUDOKU::EndGen(int end_boards, Write_File* write_out) {
    string result = "";
    string first_line;
    int16 diff[DIM], index, j;
    char c;
    srand((unsigned)time(NULL));
    for (int i = 0; i < end_boards; i++) {
        for (int j = 0; j < DIM; j++) {
            diff[j] = 0;
        }
        first_line = "";
        j = 0;
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
        result = result + align_string(first_line);
    }
    if (result == "") {
        return false;
    }
    write_out->write_data(result);
    return true;
}

bool SUDOKU::StartGen(int start_boards, Write_File* write_out, int blanks, bool distinct) {
    if (blanks < 1 || blanks > 64) {
        return false;
    }
    int ran_i, ran_j, i, j, k = 0, cur_pos;
    int boards_number = 0;
    int diff[DIM];
    string result = "";
    char temp_board[DIM][DIM], c;
    int shift[DIM - 1] = { 3, 6, 1, 4, 7, 2, 5, 8 };
    int index[DIM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    Write_File* write_distinct = new Write_File(distinct_result);
    srand((unsigned)time(NULL));
    while (boards_number < start_boards) {
        // Get the random first row
        for (i = 0; i < DIM; i++) {
            diff[i] = 0;
        }
        j = 0;
        k = 0;
        while (j < DIM) {
            i = rand() % DIM;
            if (diff[i]) {
                continue;
            }
            c = i + 1 + '0';
            temp_board[0][k] = c;
            board[0][k] = i + 1;
            k++;
            diff[i] = 1;
            j++;
        }

        // Shift the first row
        for (int line = 1; line < DIM; line++) {
            cur_pos = shift[line - 1];
            for (int j = 0; j < DIM; j++, cur_pos++) {
                cur_pos = (cur_pos == DIM) ? 0 : cur_pos;
                temp_board[line][j] = temp_board[0][index[cur_pos]];
                board[line][j] = board[0][index[cur_pos]];
            }
        }

        // Set blanks
        // 2 blanks each row
        for (i = 0; i < DIM; i++) {
            j = 0;
            while (j < 2) {
                ran_j = rand() % DIM;
                if (temp_board[i][ran_j] == '$')
                    continue;
                temp_board[i][ran_j] = '$';
                board[i][ran_j] = 0;
                j++;
            }
        }
        // Random position
        k = 0;
        while (k < blanks - 2*DIM) {
            ran_i = rand() % DIM;
            ran_j = rand() % DIM;
            if (temp_board[ran_i][ran_j] == '$')
                continue;
            temp_board[ran_i][ran_j] = '$';
            board[ran_i][ran_j] = 0;
            k++;
        }

        // Check if the answer is distinct
        if (distinct) {
            int result_num = Backtrack(write_distinct);
            if (result_num > 1)
                continue;
        }

        // Output
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                result = result + temp_board[i][j] + ' ';
            }
            result = result + '\n';
        }
        result = result + '\n';
        boards_number++;
    }
    write_out->write_data(result);
    delete write_distinct;
    return true;
}
