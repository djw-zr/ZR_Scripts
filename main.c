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

int load_sigscr_file(char *or_route_dir, char *script_file) ;
int print_sigscr_tree(nodeType *p) ;
int print_sigscr_names(nodeType *p) ;

nodeType *sTree = NULL;

int main(int argc, char *argv[]) {


      printf("  Start program main\n") ;
#if 1
      load_sigscr_file(".","sigscr.dat") ;
#else
      load_sigscr_file(".","sigscr_test_1.dat") ;
      load_sigscr_file(".","sigscr_test_2.dat") ;
      load_sigscr_file(".","sigscr_eur1.dat") ;
#endif
      printf("\n  PRINT TREE\n\n") ;
      print_sigscr_tree(sTree) ;

      printf("\n  PRINT LIST\n\n") ;
      print_sigscr_names(sTree) ;

      printf("\n  End program main\n\n") ;

      return 0;
}
