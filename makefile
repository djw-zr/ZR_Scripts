#
################################################################################
#
#   File: makefile
#
#   Makefile using flex and bison to generate a compiler for
#   KUJU/MSTS style signal  scripts and to test the compiler using
#   a 'C' program.
#
#   This file was developed for use with ZR. It is released under
#   licence GPL-3.0-or-later.   You should have received a copy of the
#   GNU General Public License along with this file.  If not, see
#   <https://www.gnu.org/licenses/>.
#
################################################################################
#
#SHELL      = /bin/sh

#  Specify C Compiler and Compiler Options
CC       = gcc

# Which suffixes to process
.SUFFIXES:
.SUFFIXES: .h .o .c .l .y

#  Targets that are not the name of a file
.PHONEY: clean

#  Makefile targets:

main:   y.tab.o y.tab.h lex.yy.o sigscr.o main.o makefile
	$(CC) lex.yy.o y.tab.o sigscr.o main.o -o main

.c.o:   makefile y.tab.h y.tab.c lex.yy.c
	$(CC) -c $*.c

lex.yy.c:  bas.l y.tab.h sigscr.h
	flex bas.l

y.tab.c: y.tab.h

y.tab.h: bas.y sigscr.h
	bison -dy -Dparse.trace bas.y

clean:
	rm -f main *.o lex.yy.c y.tab.h y.tab.c *~ y.output

