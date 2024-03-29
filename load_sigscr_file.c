/*
 *==============================================================================
 *345678901234567890123456789012345678901234567890123456789012345678901234567890
 *
 *   File:  load_sigscr_file.c
 *   Copyright 2022  David J. Webb
 *
 *   File contains subroutines for processing the signal script trees
 *   generated by the bison program.
 *
 *   This file is not compiled separately.  It is included by file lex.yy.c
 *   and is compiled at the same time as that file.
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
#include <string.h>
#include "sigscr.h"
#include "y.tab.h"

extern int yydebug ;
extern nodeType *sTree;

FILE   *yyin, *yyout ;

int    yyparse(nodeType **sTree) ;
void   yyset_in(FILE *sfile)     ;
int    print_sigscr_node(nodeType *p) ;

int         itree_depth = 0 ;
/*
 *  Array 'token' is used by routine 'print_sigscr_tree' to give sense to the
 *  set of enums defined in array 'yytokentype' of file 'y.tab.h'.  The
 *  latter is generated by the bison program.  If 'yytokentype' changes then
 *  array 'token' needs to be changed as well.
 */
static char *token[] = {
    "PROGRAM",
    "FUNCTION",
    "VARIABLE",
    "NAME",
    "IVALUE",
    "FVALUE",
    "SCRIPT",
    "EXTERN",
    "FLOAT",
    "IF",
    "ELSE",
    "FOR",
    "WHILE",
    "DO",
    "BREAK",
    "CONTINUE",
    "RETURN",
    "PRINT",
    "UMINUS",
    "SCRIPT_LIST",
    "DEF_LIST",
    "STMT_LIST",
    "DEF_EFUN",
    "DEF_EVAR",
    "DEF_VAR",
    "EXIT",
    "ASSIGN",
    "IAS",
    "PE",
    "ME",
    "XE",
    "DE",
    "IASD",
    "IMD",
    "IFX",
    "BB",
    "NO_OP",
    "NEG",
    "COMMA",
    "EXPR_LIST",
    "AND",
    "OR",
    "EOR",
    "NOT",
    "INT",
    "GT",
    "LT",
    "GE",
    "LE",
    "EQ",
    "NE",
    "IGT",
    "ILT",
    "IGE",
    "ILE",
    "IEQ",
    "INE",
    "POW"
} ;

/*
 *  Routine to read signal script file and initialise the tree pointer sTree.
 */
#if 0
int read_sigscr_file(){

int  ip = 1 ;
int  iret ;

      yydebug = 0 ;

      yyin = fopen(file_in1, "r");
      if(ip)printf("  File opened : %s\n",file_in1) ;
      yyset_in(yyin) ;
      iret = yyparse(&sTree);
      if(ip)printf("  Close file \n") ;
      fclose(yyin);
      if(iret){
        printf("  Unable to parse signal script file 1\n");
        printf("  Error return value = %i\n",iret);
        exit(0) ;
      }
/*
 *  Test for two script files
 */
#if 1
      yyin = fopen(file_in2, "r");
      if(ip)printf("  File opened : %s\n",file_in2) ;
      yyset_in(yyin) ;
      iret = yyparse(&sTree);
      if(ip)printf("  Close file \n") ;
      fclose(yyin);
      if(iret){
        printf("  Unable to parse signal script file 2\n");
        printf("  Error return value = %i\n",iret);
        exit(0) ;
      }
#endif
/*
 *  Test for three script files
 */
#if 1
      yyin = fopen(file_in3, "r");
      if(ip)printf("  File opened : %s\n",file_in2) ;
      yyset_in(yyin) ;
      iret = yyparse(&sTree);
      if(ip)printf("  Close file \n") ;
      fclose(yyin);
      if(iret){
        printf("  Unable to parse signal script file 2\n");
        printf("  Error return value = %i\n",iret);
        exit(0) ;
      }
#endif
      if(!ip) return 0 ;
      printf("  sTree = %p\n",(void *)sTree) ;
      printf("  sTree->type = %i\n",sTree->type) ;
      printf("  sTree->opr.oper = %i\n",sTree->opr.oper) ;
      printf("  sTree->opr.nops = %i\n",sTree->opr.nops) ;

      printf("\n PRINT TREE\n") ;
      print_sigscr_node(sTree) ;

      printf("\n PRINT NAMES\n\n") ;
      print_sigscr_names(sTree) ;

      return 0 ;
}
#else
int load_sigscr_file(char *or_route_dir, char *script_file){

  int  ip = 0 ;
  int  l, iret ;
  char *string = NULL,
       *my_name = "read_sigscr_file" ;

      if(ip)printf("  Enter routine %s\n",my_name) ;
      yydebug = 0 ;

/*
 *  The file sigcfg.dat should be in the main "Route" directory (ORRoutedir))
 */
      l = strlen(or_route_dir) + strlen(script_file) + 2;
      string = (char *) malloc(l) ;
      strcpy(string,or_route_dir) ;
      strcat(string,"/")  ;
      strcat(string,script_file)  ;
/*
 *  Check file exists
 */
      if(ip)printf("  Routine %s.  Opening file %s\n",my_name,string) ;
      yyin = fopen(string,"r") ;
      if(yyin == NULL){
        printf("  Unable to find sigscr.dat file\n") ;
        printf("     Full filename = %s\n",string) ;
        printf("  Program stopping ...\n") ;
        exit(1) ;
      }
      printf("     File opened : %s\n",string) ;
      free(string) ;
/*
 *   Parse file
 */
      yyset_in(yyin) ;
      iret = yyparse(&sTree);
      if(iret){
        printf("  Unable to parse signal script file\n");
        printf("  Error return value = %i\n",iret);
        exit(0) ;
      }
      if(ip)printf("  Close file \n") ;
      fclose(yyin);
/*
 *  Print summary
 */
      if(ip){
        printf("  sTree = %p\n",(void *)sTree) ;
        printf("  sTree->type = %i\n",sTree->type) ;
        printf("  sTree->opr.oper = %i\n",sTree->opr.oper) ;
        printf("  sTree->opr.nops = %i\n",sTree->opr.nops) ;

        printf("\n PRINT TREE\n") ;
        print_sigscr_node(sTree) ;
      }

      return 0 ;
}
#endif

int print_sigscr_node(nodeType *p){

int i, n, nops, oper, type ;

      if(p == NULL) return 0 ;
      type = p->type ;
      if(type == typeStr){
        for(i=0;i<itree_depth;i++)printf("  ") ;
        printf("  psn : str :: name = %s\n",p->str.name) ;
      }else if( type == typeOpr){
        oper = p->opr.oper ;
        nops = p->opr.nops ;
        for(i=0;i<itree_depth;i++)printf("  ") ;
        if(oper >= SC_PROGRAM && oper <= SC_POW){
          printf("  psn : opr :: %i %i %s\n",nops,oper,token[oper-SC_PROGRAM]);
        }else{
          printf("  psn : opr :: %i %i %s\n",nops,oper,"INDEX OUT OF RANGE");
        }
        itree_depth++ ;
        for(n=0;n<nops;n++){
          print_sigscr_node(p->opr.op[n]);
        }
        itree_depth-- ;
      }else{
        printf(" ERROR in routine print_sigscr_node\n");
        printf(" psn ::     type = %i\n",type) ;
        exit(0) ;
      }
      return 0 ;
}

int print_sigscr_tree(nodeType *p){

int ip = 0 ;

      if(!p)return 0 ;
      if(ip){
        printf("  ENTER  print_sigscr_tree\n") ;
        printf("  Tree pointer = %p\n",(void *)p) ;
      }
      itree_depth = 0 ;
      print_sigscr_node(p) ;
      return 0 ;
}

/*
 *  Routine to print the names of the scripts held in a script tree
 */

int print_sigscr_names(nodeType *p){

nodeType *p1, *p2 ;
int i, n, nops, oper, type ;

      if(p == NULL) return 0;
      p1 = p ;
/*
 *  Skip initial program tag
 */
      oper = p1->opr.oper ;
      if(oper == SC_PROGRAM)p1 = p1->opr.op[0] ;
/*
 *  Loop overt SC_SCRIPT_LISTs
 */
      for(;;){
/*
 *  Return if end of list
 */
        if(p1 == NULL) return 0 ;
        oper = p1->opr.oper ;
/*
 *  Find SC_SCRIPT
 */
        if(oper == SC_SCRIPT_LIST){
          p2 = p1->opr.op[1] ;
          oper = p2->opr.oper ;
/*
 *  Find and print SCRIPT NAME
 */
          if(oper == SC_SCRIPT){
            p2 = p2->opr.op[0] ;
            oper = p2->opr.oper ;
            printf("  Script = %s\n",p2->str.name) ;
          }
        }else{
/*
 *  ERROR
 */
          break ;
        }
        p1 = p1->opr.op[0] ;
      }
      return 0 ;
}


/*
 *  Routine to return the character string corresponding to a
 *  script token.
 */

char *sigscr_token_string(int i){

      if(i < SC_PROGRAM && i > SC_POW) return NULL ;
      return token[i-SC_PROGRAM] ;
}
