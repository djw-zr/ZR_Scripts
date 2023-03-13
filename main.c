/*
 *==============================================================================
 *345678901234567890123456789012345678901234567890123456789012345678901234567890
 *
 *   File:  main.c
 *   Copyright 2022  David J. Webb
 *
 *   Main program for testing the 'compiling' of MSTS signal scripts
 *   using bison and lex.  The scheme is being developed for possible
 *   use in ZR.
 *
 *   The order at which programs should be compiled is:
 *
 *      bison -dy -Dparse.trace bas.y
 *      lex bas.l
 *      gcc lex.yy.c y.tab.c main.c -lm -o main
 *
 *   Released under licence GPL-3.0-or-later
 *
 *   ZR is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ZR is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ZR.  If not, see <https://www.gnu.org/licenses/>.
 *
 *==============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sigscr.h"
#include "y.tab.h"

int      read_sigscr_file() ;


int main(int argc, char *argv[]) {

      read_sigscr_file() ;

      return 0;
}
