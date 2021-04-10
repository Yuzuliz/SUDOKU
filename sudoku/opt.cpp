#include "opt.h"
#include "File_Operation.h"
#include "SUDOKU.h"

bool get_range(string arg, int* range_min, int* range_max)
{
    cout << "开始获取范围" << endl;
    unsigned int i = 0;
    for (; i < arg.size(); i++)
    {
        if (arg[i] == '~') break;
    }
    if (i <= 0 || i >= arg.size() - 1) return 0;
    string range_min_str = "", range_max_str = "";
    for (unsigned int j = 0; j < i; j++) range_min_str = range_min_str + arg[j];
    for (unsigned int j = i + 1; j < arg.size(); j++) range_max_str = range_max_str + arg[j];
    range_min_str = range_min_str + "\0";
    range_max_str = range_max_str + "\0";
    cout << "范围获取结束" << endl;
    *range_min = atoi(range_min_str.c_str());
    *range_max = atoi(range_max_str.c_str());
    return 1;
}

opt::~opt()
{
    delete this->sudoku;
}

bool opt::get_opt(int argc, char* argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
        printf("optarg = %s\n", optarg); // 参数内容
        printf("optind = %d\n", optind); // 下一个被处理的下标值
        printf("argv[optind - 1] = %s\n\n", argv[optind - 1]); // 参数内容
        switch (opt)
        {
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

bool opt::do_solve_board()
{
    try
    {
        Read_File read_obj(this->opt_type_arg);
        Write_File *write_obj = new Write_File(Output_Path);
        int result_num;
        while (!read_obj.read_eof())
        {
            if (!read_obj.read_data()) break;
            //read_obj.show_board();
            cout << endl;
            change_char_2_int(read_obj.board, board);
            this->sudoku->Display(write_obj, "当前状态: ");
            result_num = sudoku->Backtrack(write_obj);
            if (!result_num)
            {
                cout << "运算失败，请检查输入是否合法！" << endl;
                delete write_obj;
                return 0;
            }
            else
            {
                printf("运算成功，共有%d个结果，请查看%s\n",result_num,Output_Path.c_str());
            }
        }
        delete write_obj;
        return 1;
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
        return 0;
    }
}

bool opt::do_end_board()
{
    int board_numbers = atoi(this->opt_type_arg.c_str());
    cout << board_numbers << endl;
    try
    {
        Write_File* write_obj = new Write_File(gen_path_end);
        if (!this->sudoku->EndGen(board_numbers, write_obj))
        {
            cout << "终局生成失败，请检查后重试！" << endl;
            return 0;
        }
        else
        {
            cout << "终局生成成功，请查看" << gen_path_end << endl;
        }
        return 1;
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
        return 0;
    }
}

bool opt::do_gen_board()
{
    int board_numbers = atoi(this->opt_type_arg.c_str());
    int hole_numbers = 25;
    bool distinct = 0;
    switch (this->opt_append)
    {
    case 0:
        break;
    case Difficulty:
        switch (atoi(this->opt_append_arg.c_str()))
        {
        case 1:
            hole_numbers = 10;
            break;
        case 2:
            hole_numbers = 30;
            break;
        case 3:
            hole_numbers = 50;
            break;
        default:
            cout << "难度选择有误" << endl;
            return 0;
        }
        break;
    case HoleNumbers:
        int hole_numbers_min, hole_numbers_max;
        if (!get_range(this->opt_append_arg, &hole_numbers_min, &hole_numbers_max))
        {
            cout << "挖空范围输入有误，请查看操作是否正确" << endl;
            return 0;
        }
        srand((unsigned)time(NULL));
        hole_numbers = hole_numbers_min + rand() % (hole_numbers_max - hole_numbers_min + 1);
        cout << "挖空个数为" << hole_numbers << endl;
        break;
    case OnlySolution:
        distinct = 1;
        break;
    default:
        cout << "附加参数有误" << endl;
        return 0;
    }
    try
    {
        Write_File* write_obj = new Write_File(gen_path_start);
        if (!this->sudoku->StartGen(board_numbers, write_obj, hole_numbers, distinct))
        {
            cout << "初局生成失败，请检查后重试！" << endl;
            delete write_obj;
            return 0;
        }
        else
        {
            cout << "初局生成成功，请查看" << gen_path_start << endl;
        }
        delete write_obj;
        return 1;
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
        return 0;
    }
}

bool opt::do_opt()
{
    if (this->opt_type == SOLVE_BOARD)
    {
        if (!this->do_solve_board())
        {
            cout << "解局失败，请查看操作是否正确" << endl;
            return 0;
        }
    }
    else if (this->opt_type == END_BOARD)
    {
        if (!this->do_end_board())
        {
            cout << "终局生成失败，请查看操作是否正确" << endl;
            return 0;
        }
    }
    else if (this->opt_type == GEN_BOARD)
    {
        if (!this->do_gen_board())
        {
            cout << "题目生成失败，请查看操作是否正确" << endl;
            return 0;
        }
    }
    else
    {
        cout << "不存在的状态，请查看操作是否正确" << endl;
        return 0;
    }
    return 1;
}