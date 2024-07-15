#
################################################################################
#
#   File: makefile
#
#   Makefile for compiling code using bison and lex
#
#   For use with ZR the generated files 'lex.yy.c' and 'y.tab.c' should be
#   copied to the ZR 'src/input' directory.  The file y.tab.h should
#   be copied to the ZR 'include' directory.
#
#   This file is part of ZR. Released under licence GPL-3.0-or-later.
#   You should have received a copy of the GNU General Public License
#   along with ZR.  If not, see <https://www.gnu.org/licenses/>.
#
################################################################################
#
#SHELL      = /bin/sh

# Define interface: SDL2 or (default) GLUT
# This does not work if # follows SDL2
#IFACE=SDL2


#  Specify Compiler and Compiler Options
CC       = gcc

# Which suffixes to process
.SUFFIXES:
.SUFFIXES: .h .o .c .l .y

#  Targets that are not the name of a file
.PHONEY: clean

#  Makefile targets:

main:   y.tab.o y.tab.h lex.yy.o load_sigscr_file.o main.o makefile
	$(CC) lex.yy.o y.tab.o load_sigscr_file.o main.o -o main

.c.o:   makefile y.tab.h y.tab.c lex.yy.c
	$(CC) -c $*.c

lex.yy.c:  bas.l y.tab.h sigscr.h
	lex bas.l

y.tab.c: y.tab.h

y.tab.h: bas.y sigscr.h
	bison -dy -Dparse.trace bas.y

clean:
	rm -f main *.o lex.yy.c y.tab.h y.tab.c *~ y.output

