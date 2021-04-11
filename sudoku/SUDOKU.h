// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include "common.h"
#include "File_Operation.h"


class SUDOKU {
    string Output_Path;
 public:
    SUDOKU() {}
    explicit SUDOKU(string output) :Output_Path(output) {}

    bool CorrectPlace(int x, int y);

    void Display(Write_File *write_obj, string ps = "");

    int Backtrack(Write_File *write_obj, int t = 0, bool write_out = 1, bool distinct = 0);

    bool EndGen(int end_boards, Write_File *write_out);

    bool StartGen(int start_boards, Write_File* write_out, 
        int blanks_min = 25, int blanks_max = 55, bool distinct = 0);
};

// Shift the first row to get the other rows
string align_string(string a);
string gen_first_line();
bool set_blanks(Write_File* write_out, int blanks);

#endif  // SUDOKU_H_
