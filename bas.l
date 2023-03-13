/*
 *==============================================================================
 *345678901234567890123456789012345678901234567890123456789012345678901234567890
 *
 *   File:  bas.i
 *
 *   Lex file for splitting MSTS Signal Scripts into tokens.  Lex generates
 *   a C file "lex.yy.c" containing the routine "yy_lex".  This is called by
 *   routine yyparse in file y.tab.c, which then uses the tokens while to
 *   parse the script and generate a tree representing the sequence of commands
 *   within the script.
 *
 *   The order at which programs should be compiled is:
 *
 *      bison -dy -Dparse.trace bas.y
 *      lex bas.l
 *      gcc lex.yy.c y.tab.c main.c -lm -o main
 *
 *   This file is based on information and example code published in:
 *
 *   Charles Donnelly and Richard Stallman, Bison (version 3.8.1),
 *   Free Software Foundation Boston, MA, USA.
 *      https://www.gnu.org/software/bison/manual/bison.pdf
 *   Tom Niemann, Lex & Yacc Tutorial, epaperpress.com, Portland, Oregon, USA.
 *      https://www.epaperpress.com/lexandyacc/
 *
 *   The MSTS script file specification, is given in document
 *     "How_to_make_Signal_config_and_Script_files.doc"
 *   The file can be generated by running program "techdocs.exe" in folder
 *   techdocs contained in the first of the two MSTS disks.
 *
 *   This file is released under licence GPL-3.0-or-later
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
/*  Definitions   */
%{
#include <stdio.h>
#include <math.h>
#include "sigscr.h"
#include "y.tab.h"
void yyerror(char *) ;
char *string ;
int ip1 = 0 ;
%}

%x rem
/*
Summary of Lex Pattern Matching Primitives (Niemann, Table 1), Niemann also
gives examples (Table 2).

Metacharacter   Matches
.               any character except newline
\n              newline
*               zero or more copies of the preceding expression
+               one or more copies of the preceding expression
?               zero or one copy of the preceding expression
^               beginning of line
$               end of line
a|b             a or b
(ab)+           one or more copies of ab (grouping)
"a+b"           literal "a+b" (C escapes still work)
[]              character class

The linux manual page "man lex" gives more detailed information on
how regular expressions in Lex differ from the POSIX standard.  See:
  https://www.man7.org/linux/man-pages/man1/lex.1p.html
  https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap09.html

Note:  lex matches the longest possible string
       In the case of a tie it matches the first pattern
       The <rem> lines are used to skip over SCRIPTS commented
       out by the use of "REM"

Note:  "//".*$ causes two "warning, dangerous trailing context" messages
       but these do not appear to affect normal parsing.
       These messages stop after removing the '$', instead there are six
       "warning, rule cannot be matched" messages for the lines in which
       'AND' and related tokens are defined.
*/
/*
 Old SCRIPT line
<rem>^"SCRIPT"  {
                printf(" lex: rem SCRIPT\t%s\n",yytext) ;
                BEGIN(INITIAL) ;
                return SCRIPT ;
               }


 */

/*  Rules         */
%%
                    /*  Commented out script */
^"REM".*"SCRIPT"     {
                       BEGIN(rem) ;
                       if(ip1)printf(" lex found REM:\t%s\n\n",yytext) ;
                     }
                    /*  Everything until the next SCRIPT */
<rem>^[^"SCRIPT"\n].*\n {
                       if(ip1)printf(" lex: rem line:\t%s\n",yytext);
                     }
                     /*  Normal SCRIPT and script name */
<INITIAL,rem>"SCRIPT"[ \t]+[a-zA-Z][a-zA-Z0-9_\-\+]* {
                        BEGIN(INITIAL) ;
                        string = strrchr(yytext,' ') ;
                        string ++ ;
                        yylval.sValue = strdup(string) ;
                        if(ip1)printf(" lex found SCRIPT : NAME = \t%s\n",string) ;
                        return SC_SCRIPT ;
                      }
"extern"  return SC_EXTERN ;
"float"   return SC_FLOAT  ;
"if"      return SC_IF     ;
"else"    return SC_ELSE   ;
"for"     return SC_FOR    ;
"while"   return SC_WHILE  ;
"do"      return SC_DO     ;
"break"   return SC_BREAK  ;
"continue" return SC_RETURN ;
"return"  return SC_RETURN ;
"print"   return SC_PRINT  ;
"exit"    return SC_EXIT   ;
"and"     return SC_AND    ;
"or"      return SC_OR     ;
"eor"     return SC_EOR    ;
"not"     return SC_NOT    ;

[a-zA-Z][a-zA-Z0-9_]*     {
                           if(ip1)printf(" lex: NAME:\t%s\n",yytext);
                           yylval.sValue = strdup(yytext) ;
                           return SC_NAME ;
                          }
[+-]?[0-9]*               {
                           if(ip1)printf(" lex: INTEGER :\t%s\n",yytext);
                           yylval.sValue = strdup(yytext) ;
                           return SC_IVALUE ;
                          }
[+-]?[0-9]+([.]?[0-9]*)?([eE][+-]?[0-9]+)?|[+-]?[.][0-9]+([eE][+-]?[0-9]+)? {
                           if(ip1)printf(" lex: FLOAT   :\t%s\n",yytext);
                           yylval.sValue = strdup(yytext) ;
                           return SC_FVALUE ;
                          }
[-()=*+/;{}.!^]          return *yytext;

"()"      return SC_BB  ;
","       return SC_COMMA ;

"&&"      return SC_AND ;
"||"      return SC_OR  ;

"#="      return SC_IAS ;
"+="      return SC_PE  ;
"-="      return SC_ME  ;
"*="      return SC_XE  ;
"/="      return SC_DE  ;
"/#="     return SC_IASD ;   /*  Integer Division :  Convert all to int first */
"%="      return SC_AMD ;

">#"      return SC_IGT ;
"<#"      return SC_ILT ;
">=#"     return SC_IGE ;
"<=#"     return SC_ILE ;
"==#"     return SC_IEQ ;
"!=#"     return SC_INE ;

">="      return SC_GE  ;
"<="      return SC_LE  ;
"=="      return SC_EQ  ;
"!="      return SC_NE  ;

">"       return SC_GT  ;
"<"       return SC_LT  ;

"**"      return SC_POW ;


[ \t\n\r]+                { ;}   /* ignore whitespace */
"//".*$                   { ;}   /* ignore single line comments */
"/*"[^(*/)]*"*/"          { ;}   /* ignore standard comment */
.         yyerror(" Lex : Unknown character.") ;
%%

/*  Return 1 at end of line */
int yywrap(void) {
      return 1;
}

/*  Main program for running lexical analyser by itself */
/*
 [+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)  printf(" FLOAT  %s\n", yytext) ;
  [0-9]+          printf(" INTEGER  %s\n", yytext) ;
^(.*)\n printf(" LINE:\t%s", yytext);
 */
/*
int main(int argc, char *argv[]) {
      yyin = fopen(argv[1], "r");
      yylex();
      fclose(yyin);
}
*/