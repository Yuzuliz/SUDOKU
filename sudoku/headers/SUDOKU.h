// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include "./common.h"
#include "./File_Operation.h"


class SUDOKU {
    string Output_Path;
 public:
    SUDOKU() {}
    explicit SUDOKU(string output) :Output_Path(output) {}

    bool CorrectPlace(int x, int y);

    void Display(Write_File *write_obj, string ps = "");

    int Backtrack(Write_File *w_obj, int t = 0, bool w = 1, bool distinct = 0);

    bool EndGen(int end_boards, Write_File *write_out);

    bool StartGen(int num, Write_File* w,
        int b_min = 25, int b_max = 55, bool d = 0);
};

// Shift the first row to get the other rows
string align_string(string a);
string gen_first_line();
bool set_blanks(Write_File* write_out, int blanks);

#endif  // SUDOKU_H_
