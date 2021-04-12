// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#ifndef SUDOKU_OPT_H_
#define SUDOKU_OPT_H_

#include "common.h"
#include "SUDOKU.h"

enum { END_BOARD = 1, SOLVE_BOARD, GEN_BOARD };  // mode
enum { Difficulty = 1, HoleNumbers, OnlySolution };

class opt {
 public:
    opt() :opt_type(0), opt_append(0) { sudoku = new SUDOKU(Output_Path); }
    ~opt();
    bool get_n_arg(int &hole_num_min, int &hole_num_max, bool &distinct);
    bool get_opt(int argc, char* argv[]);
    bool do_solve_board();
    bool do_end_board();
    bool do_gen_board();
    bool do_opt();
    int opt_type;
    string opt_type_arg;
    int opt_append;
    string opt_append_arg;
 private:
    SUDOKU* sudoku;
};

bool get_range(string arg, int* range_min, int* range_max);

#endif  // SUDOKU_OPT_H_
