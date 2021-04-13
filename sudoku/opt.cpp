// Copyright 2021 Yingtong_Yu Yifei_Guo

#include <string>
#include "./headers/opt.h"
#include "./headers/File_Operation.h"
#include "./headers/SUDOKU.h"

bool get_range(string arg, int* range_min, int* range_max) {
    unsigned int i = 0;
    for (; i < arg.size(); i++) {
        if (arg[i] == '~') break;
    }
    if (i <= 0 || i >= arg.size() - 1) return 0;
    string range_min_str = "", range_max_str = "";
    for (unsigned int j = 0; j < i; j++)
        range_min_str = range_min_str + arg[j];
    for (unsigned int j = i + 1; j < arg.size(); j++)
        range_max_str = range_max_str + arg[j];
    range_min_str = range_min_str + "\0";
    range_max_str = range_max_str + "\0";
    *range_min = atoi(range_min_str.c_str());
    *range_max = atoi(range_max_str.c_str());
    return 1;
}

opt::~opt() {
    delete this->sudoku;
}

bool opt::get_n_arg(int &hole_num_min, int &hole_num_max, bool &distinct) {
    switch (this->opt_append) {
    case 0:
        break;
    case Difficulty:
        switch (atoi(this->opt_append_arg.c_str())) {
        case 1:
            hole_num_min = 10;
            hole_num_max = 20;
            break;
        case 2:
            hole_num_min = 30;
            hole_num_max = 40;
            break;
        case 3:
            hole_num_min = 50;
            hole_num_max = 60;
            break;
        default:
            cout << "ERROR LEVEL!" << endl;
            return 0;
        }
        break;
    case HoleNumbers:
        if (!get_range(opt_append_arg, &hole_num_min, &hole_num_max)) {
            cout << "ERROR RANGE!" << endl;
            return 0;
        }
        break;
    case OnlySolution:
        distinct = 1;
        break;
    default:
        cout << "ERROR ATTRIBUTE!" << endl;
        return 0;
    }
    return 1;
}

bool opt::get_opt(int argc, char* argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        printf("opt = %c\n", opt);  // -a -b -c -d
        printf("optarg = %s\n", optarg);  // -a 3
        printf("optind = %d\n", optind);  // next pos
        printf("argv[optind - 1] = %s\n\n", argv[optind - 1]);
        switch (opt) {
        case 'c':
            if (this->opt_type != 0) return 0;
            this->opt_type = END_BOARD;
            this->opt_type_arg = optarg;
            break;
        case 's':
            cout << this->opt_type << endl;
            if (this->opt_type != 0) return 0;
            this->opt_type = SOLVE_BOARD;
            this->opt_type_arg = optarg;
            break;
        case 'n':
            if (this->opt_type != 0) return 0;
            this->opt_type = GEN_BOARD;
            this->opt_type_arg = optarg;
            break;
        case 'm':
            if (this->opt_append != 0) return 0;
            this->opt_append = Difficulty;
            this->opt_append_arg = optarg;
            break;
        case 'r':
            if (this->opt_append != 0) return 0;
            this->opt_append = HoleNumbers;
            this->opt_append_arg = optarg;
            break;
        case 'u':
            if (this->opt_append != 0) return 0;
            this->opt_append = OnlySolution;
            break;
        }
    }
    if (this->opt_append != 0 && this->opt_type != GEN_BOARD) return 0;
    if (this->opt_type == 0) return 0;
    return 1;
}

bool opt::do_solve_board() {
    try {
        Read_File read_obj(this->opt_type_arg);
        Write_File *write_obj = new Write_File(Output_Path);
        int result_num;
        while (!read_obj.read_eof()) {
            if (!read_obj.read_data()) break;
            cout << endl;
            change_char_2_int(read_obj.board, board);
            this->sudoku->Display(write_obj, "Start: ");
            result_num = sudoku->Backtrack(write_obj);
            if (!result_num) {
                cout << "Calculation failed.Please check the start board!\n";
                delete write_obj;
                return 0;
            } else {
                cout << "Calculation succeeded. ";
                printf("%d results in total. ", result_num);
                printf("Output filepath: %s\n", Output_Path.c_str());
            }
        }
        delete write_obj;
        return 1;
    }
    catch (const char* msg) {
        cerr << msg << endl;
        return 0;
    }
}

bool opt::do_end_board() {
    int board_num;
    try {
        board_num = atoi(this->opt_type_arg.c_str());
    }
    catch (exception) {
        cerr << "wrong parameter" << endl;
        return 0;
    }
    try {
        Write_File* write_obj = new Write_File(gen_path_end);
        if (!this->sudoku->EndGen(board_num, write_obj)) {
            cout << "Final board generation failed." << endl;
            return 0;
        } else {
            cout << "Final board generation succeeded. File path: ";
            cout << gen_path_end << endl;
        }
        return 1;
    }
    catch (const char* msg) {
        cerr << msg << endl;
        return 0;
    }
}

bool opt::do_gen_board() {
    int boards = atoi(this->opt_type_arg.c_str());
    int blank_min = 25, blank_max = 55;
    bool distinct = 0;
    if (!this->get_n_arg(blank_min, blank_max, distinct)) {
        cout << "get append args failed!" << endl;
        return 0;
    }
    try {
        Write_File* w_obj = new Write_File(gen_path_start);
        if (!sudoku->StartGen(boards, w_obj, blank_min, blank_max, distinct)) {
            cout << "Original board generation failed." << endl;
            delete w_obj;
            return 0;
        } else {
            cout << "Original board generation succeeded. File path: ";
            cout << gen_path_start << endl;
        }
        delete w_obj;
        return 1;
    }
    catch (const char* msg) {
        cerr << msg << endl;
        return 0;
    }
}

bool opt::do_opt() {
    if (this->opt_type == SOLVE_BOARD) {
        if (!this->do_solve_board()) {
            cout << "Cannot solve the question!" << endl;
            return 0;
        }
    } else if (this->opt_type == END_BOARD) {
        if (!this->do_end_board()) {
            cout << "Cannot generate the final board!" << endl;
            return 0;
        }
    } else if (this->opt_type == GEN_BOARD) {
        if (!this->do_gen_board()) {
            cout << "Cannot generate the original board!" << endl;
            return 0;
        }
    } else {
        cout << "ERROR OPTION!" << endl;
        return 0;
    }
    return 1;
}
