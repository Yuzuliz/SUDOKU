#pragma once
#ifndef _OPT_H
#define _OPT_H

#include "common.h"

const char* optstring = "c:s:n:m:r:u"; // ���ö̲������ͼ��Ƿ���Ҫ����
enum { END_BOARD = 1, SOLVE_BOARD, GEN_BOARD };  // ��ǰҪ���еĲ���
enum { Difficulty = 1, HoleNumbers, OnlySolution };

class opt
{
public:
	opt() :opt_type(0), opt_append(0) {}
	bool get_opt(int argc, char* argv[]);
	bool do_solve_board();
	bool do_end_board();
	bool do_gen_board();
	bool do_opt();

private:
	int opt_type;
	string opt_type_arg;
	int opt_append;
	string opt_append_arg;

};

#endif // !_OPT_H
