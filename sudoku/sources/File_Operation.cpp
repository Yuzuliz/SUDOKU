// Copyright 2021 Yingtong_Yu Yifei_Guo

#pragma once
#include <string>
#include "./File_Operation.h"
Write_File::Write_File(string file) {
    // output
    try {
        this->WriteFile.open(file, ios::out);
    }
    catch (exception) {
        throw "error occured while opening a file to write";
    }
    if (!this->WriteFile.is_open()) {
        throw "Output file cannot open";
    }
    cout << "Output file " << file << " open" << endl;
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            this->board[i][j] = 0;
}

Write_File::~Write_File() {
    this->WriteFile.close();
}

bool Write_File::write_data() {
    // write the members into the file
    try {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++)
                this->WriteFile << this->board[i][j] << " ";
            this->WriteFile << endl;
        }
    }
    catch (exception) {
        cerr << "error occured while writing data" << endl;
        return 0;
    }
    return 1;
}

bool Write_File::write_data(string result) {
    try {
        this->WriteFile << result;
    }
    catch (exception) {
        cerr << "error occured while writing data" << endl;
        return 0;
    }
    return 1;
}

Read_File::Read_File(string file) {
    this->ReadFile.open(file, ios::in);
    if ( !this->ReadFile.is_open() ) {
        throw "The file cannot open";
    }
    cout << "Opened the file" << endl;
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            this->board[i][j] = 0;
}

Read_File::~Read_File() {
    this->ReadFile.close();
}

bool Read_File::read_data() {
    // get data from the file
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            if ( this->ReadFile.eof()) return 0;
            this->ReadFile >> this->board[i][j];
            if ( this->board[i][j] == '$') this->board[i][j] = '0';
        }
    return 1;
}

bool Read_File::read_eof() {
    if (this->ReadFile.eof()) return 1;
    return 0;
}

bool change_char_2_int(char board1[DIM][DIM], int board2[DIM][DIM]) {
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            board2[i][j] = board1[i][j] - '0';
            if (board1[i][j] == '$') board2[i][j] = 0;
        }
    return 1;
}
