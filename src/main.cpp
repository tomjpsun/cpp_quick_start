//
// main.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ncurses.h>

#include "reader_query.hpp"

int main(int argc, char* argv[])
{
	int height = 20;
	int width = 60;
	int startX = 10;
	int startY = 10;

        // ncurses
	initscr();
	refresh();
	WINDOW* win = newwin(height, width, startX, startY);
	wrefresh(win);

	ReaderQuery(1.8);

	getch();
	endwin();
}
