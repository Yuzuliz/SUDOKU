// Copyright 2021 Yingtong_Yu Yifei_Guo

#include "common.h"
#include "SUDOKU.h"
#include "File_Operation.h"
#include "opt.h"

int board[DIM][DIM] = { {0} };
const string dir = "txtFiles";
const string Output_Path = dir + "/sudoku.txt";
const string gen_path_end = dir + "/end.txt";
const string gen_path_start = dir + "/start.txt";
const string distinct_result = dir + "/distinct.txt";
const char* optstring = "c:s:n:m:r:u";  // short optstring type


bool mk_txt_dir() {
    // whether the path is valid
    if (_access(dir.c_str(), 0) == -1) {
        if (_mkdir(dir.c_str()) == -1)
            return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    // error/less/more char check
    opt my_opt;
    if (!my_opt.get_opt(argc, argv)) {
        cout << "ERROR OPTION!" << endl;
        return 0;
    }
    cout << "Got the option!" << endl;

    if (!mk_txt_dir()) {
        cout << "The directory is invalid." << endl;
        return 0;
    }

    my_opt.do_opt();  // deal with different options

    return 0;
}
