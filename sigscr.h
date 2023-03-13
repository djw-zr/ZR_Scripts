/*
 * File calc3.h
 */

typedef enum { typeCon, typeId, typeStr, typeOpr } nodeEnum;

/* constants */

typedef struct {
nodeEnum type;      /* type of node */
int value;          /* value of constant */
} conNodeType;

/* identifiers */

typedef struct {
nodeEnum type;      /* type of node */
int i;              /* subscript to ident array */
} idNodeType;

typedef struct {
nodeEnum type;      /* type of node    */
char    *name;      /* Pointer to name */
} strNodeType;

/* operators */

typedef struct {
nodeEnum type;      /* type of node */
int oper;           /* operator */
int nops;           /* number of operands */
union nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;

typedef union nodeTypeTag {
nodeEnum    type;    /* Type of node */
conNodeType con ;    /* Constants    */
idNodeType  id  ;    /* Identifiers  */
strNodeType str ;    /* Name/String  */
oprNodeType opr ;    /* Operators    */
} nodeType;

extern int sym[26];



