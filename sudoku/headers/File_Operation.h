// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#ifndef FILEOP_H_

#define FILEOP_H_

#include <string>
#include "./common.h"

class Write_File{
 public:
    explicit Write_File(string file);
    ~Write_File();
    bool write_data();
    bool write_data(string result);
    char board[DIM][DIM];
 private:
    ofstream WriteFile;
};

class Read_File{
 public:
    explicit Read_File(string file);
    ~Read_File();
    bool read_data();
    bool read_eof();
    void show_board();
    char board[DIM][DIM];
 private:
    ifstream ReadFile;
};

bool change_char_2_int(char board1[DIM][DIM], int board2[DIM][DIM]);

#endif
