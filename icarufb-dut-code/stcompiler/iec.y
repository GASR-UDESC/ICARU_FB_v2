%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atributos.h"
#include "instset.h"
#include "algcode.h"
#include "symbols.h"
#include "ecc.h"
#include "listadin.h"
#include "errors.h"
#include "instcon.h"
#include "asmltab.h"



#define YYSTYPE ATRIBUTOS
#include "lex.yy.c"


int yyerror (const char *str)
{
	/*printf("[%s] - in %s\n", str, yytext);
	print_linha();*/
	printf(": %d: %s before '%s'\n",err_getLine(), str,yytext);
	//error_exit(0);
	exit(0);
}

int operationResultType(int t1, int t2){
    if(t1 == t2){
        return t1;
    }
    if(t1 == TY_REAL || t2 == TY_REAL){
        return TY_REAL;
    }
    if(t1 == TY_INT || t2 == TY_INT){
        return TY_INT;
    }
    return TY_BYTE;
}

int getTypeSize(int type){
    switch(type){
        case TY_INT:
            return 2;
        case TY_BYTE:
            return 1;
        case TY_REAL:
            return 4;
    }
    err_printFatalError("Invalid type.");
    return 0;
}

int expr_postfix = 0;
int in_evt = 0;
int intaux;
int setConEv = 0;
char straux[100];
char straux2[100];
char straux3[100];


typedef union _data {
  float f;
  char  b[4];
} myFloat;
myFloat float_temp;

%}

%token T_FUNCTION_BLOCK T_END_FUNCTION_BLOCK T_SYSTEM T_END_SYSTEM T_DEVICE T_END_DEVICE T_CUSTOM
%token T_ALGORITHM T_END_ALGORITHM T_IN
%token T_END_FBS T_FBS T_EVENT_CONNECTIONS T_DATA_CONNECTIONS T_END_CONNECTIONS
%token T_EVENT_INPUT T_EVENT_OUTPUT T_END_EVENT
%token T_EC_STATES T_END_STATES T_EC_TRANSITIONS T_END_TRANSITIONS
%token T_VAR T_VAR_INPUT T_VAR_OUTPUT T_END_VAR
%token T_TWO_POINTS T_SEMICOLON T_ASSIGNMENT T_OP T_CP T_COMA T_POINT T_HASH T_ARROW
%token T_OR T_AND T_NOT T_XOR
%token T_GT T_LT T_EQ T_GE T_LE
%token T_ADD T_SUB T_DIV T_MUL
%token T_ID T_NUMBER T_NUMBER_REAL
%token T_AT T_TO
%token T_RESOURCE T_END_RESOURCE T_TASK
%token T_ON T_WITH
%token T_IF T_THEN T_END_IF T_ELSE T_ELSIF T_WHILE T_DO T_END_WHILE
%token T_BI_ADD T_BI_MUL T_BI_SUB T_BI_DIV T_BI_MOD T_BI_GT T_BI_GE T_BI_EQ T_BI_LT T_BI_LE T_BI_NE T_BI_SET_REG T_BI_GET_REG T_BI_GET_REG_REAL
%token T_ASM T_END_ASM T_NISND T_NIRCV T_STORE T_LOAD T_GOTO T_CONST T_IFEQ

%error-verbose

%%

StFile:

	Blocks System
	| Blocks
	| System
	;

Blocks:
    Blocks FunctionBlock
    | FunctionBlock
	| CustomFunctionBlock
    ;


/*
FunctionBlockList:
	FunctionBlockList FunctionBlock
	| FunctionBlock
	;
	*/


CustomFunctionBlock:
	T_CUSTOM T_FUNCTION_BLOCK T_ID {alg_reset();}
		EventInputListContainer
		EventOutputListContainer
		VarInputListContainer
		VarOutputListContainer
		VarListContainer{
			alg_gen(I_GOTO, 0); /* the main */
			alg_gen(I_GOTO, 2); /* the init */
			sy_generateMap($3.str);
		}
		T_ALGORITHM T_ID T_TWO_POINTS{/*if(strcmp($10.str, "ALG_INIT")!=0){printf("ALG_INIT expected (%s). \n", $11.str); exit(1);}*/
			alg_backpath(1,alg_newLabel());
			alg_gen(I_ALLOC, sy_getTotalSize());
			}
			StatementList
		T_END_ALGORITHM {
			alg_gen(I_RET,0);
			}
		T_ALGORITHM T_ID T_TWO_POINTS{/*if(strcmp($14.str, "ALG_RUN")!=0){printf("ALG_RUN expected.\n"); exit(1);}*/
			alg_backpath(0,alg_newLabel());}
			StatementList
		T_END_ALGORITHM {
			alg_gen(I_RET,0);
			}
	T_END_FUNCTION_BLOCK{
        //alg_backpath(0,ecc_generate());
        //alg_backpath(1, sy_generateInit());
        /*alg_selfPrint();*/

        sprintf(straux, "%s.asm", $3.str);
        alg_createAsmFile(straux);
        sprintf(straux, "%s.hex", $3.str);
        alg_createHexFile(straux);

        }
	;

FunctionBlock:
	T_FUNCTION_BLOCK T_ID {sy_init(); ecc_init();alg_reset();
        sy_add("__alg", TY_BYTE, 0,0);
        sy_add("__est", TY_BYTE, 0,0);
	}
		EventInputListContainer
		EventOutputListContainer
		EcStatesListContainer
		EcTransListContainer
		VarInputListContainer
		VarOutputListContainer
		VarListContainer
        {
         alg_gen(I_GOTO, 0); /* the main */
         alg_gen(I_GOTO, 0); /* the init */

            dev_addfb($2.str);
        sy_generateMap($2.str);
         sy_copyToDevice($2.str);
        /* sy_print();*/
         }

		FbContinue


	T_END_FUNCTION_BLOCK {
        alg_backpath(0,ecc_generate());
        alg_backpath(1, sy_generateInit());
        /*alg_selfPrint();*/

        sprintf(straux, "%s.asm", $2.str);
        alg_createAsmFile(straux);
        sprintf(straux, "%s.hex", $2.str);
        alg_createHexFile(straux);
		sprintf(straux, "%s.ecc", $2.str);
		ecc_genMap(straux);
        }

	;

FbContinue:
      /*VarListContainer*/
      AlgorithmList
    | FbsListContainer
      EventConnListContainer
	  DataConnListContainer
	;


EventInputListContainer:
	/* empty */
	| T_EVENT_INPUT
		EventList
	T_END_EVENT
	;

EventOutputListContainer:
	/* empty */
	| T_EVENT_OUTPUT
		EventList
	T_END_EVENT
	;
EventList:
	/* */
	| EventList  Event T_SEMICOLON {}
	/*| Event T_SEMICOLON  {}*/
	;
Event: T_ID {sy_add($1.str, TY_BYTE, 0, 1);};

EcStatesListContainer:
	T_EC_STATES
		EcStatesList
	T_END_STATES
	;
EcStatesList:
	EcStatesList EcStates
	| EcStates
	;

EcStates:
	T_ID {ecc_addState($1.str);} EcActionsList T_SEMICOLON
	;

EcActionsList:
	/* */
	| T_TWO_POINTS EcActionsListComa
	;

EcActionsListComa:
	  EcActionsListComa T_COMA EcAction
	| EcAction
	| /* */
	;

EcAction:
	   T_ID T_ARROW T_ID
			{ecc_addAlg2State("-", $1.str, $3.str);}
	|   T_ARROW T_ID
			{ecc_addAlg2State("-", NULL, $2.str);}
	|  T_ID T_ARROW
			{ecc_addAlg2State("-", $1.str,NULL);}
	;


/*
EcStates:
	T_ID T_SEMICOLON {ecc_addState($1.str);}
	| T_ID T_TWO_POINTS T_ID T_ARROW T_ID T_SEMICOLON
		{ecc_addState($1.str); ecc_addAlg2State($1.str, $3.str, $5.str);}
	| T_ID T_TWO_POINTS  T_ARROW T_ID T_SEMICOLON
        {ecc_addState($1.str); ecc_addAlg2State($1.str, NULL, $5.str);}
	| T_ID T_TWO_POINTS T_ID T_ARROW T_SEMICOLON
        {ecc_addState($1.str); ecc_addAlg2State($1.str, $3.str,NULL);}
	;
	*/

EcTransListContainer:
	T_EC_TRANSITIONS
	{expr_postfix = 1; in_evt = 1;}
		EcTransList
		{expr_postfix = 0; in_evt = 0;}
	T_END_TRANSITIONS
	;
EcTransList:
	/* */
	| EcTransList EcTrans
	/*| EcTrans*/
	;
EcTrans:
	T_ID T_TO T_ID T_ASSIGNMENT  Expr
		{
            ecc_addTrans($1.str, $3.str);
		}
		T_SEMICOLON
	;

VarInputListContainer:
	/* empty */
	| T_VAR_INPUT
		VarList
	T_END_VAR
	;
VarOutputListContainer:
	/* empty */
	| T_VAR_OUTPUT
		VarList
	T_END_VAR
	;
VarListContainer:
	/* empty */
	| T_VAR
		VarList
	T_END_VAR
	;
VarList:
	/* */
	| VarList VarDecl
	/*| VarDecl*/
	;
VarDecl:
	T_ID T_TWO_POINTS T_ID VarDeclAssig T_SEMICOLON {

        if(strcmp($3.str, "INT")==0){
            intaux = TY_INT;
        }else
        if(strcmp($3.str, "REAL")==0){
            intaux = TY_REAL;
        }else
        if(strcmp($3.str, "BYTE")==0){
            intaux = TY_BYTE;
        }else
        if(strcmp($3.str, "BOOL")==0){
            intaux = TY_BOOL;
        }else{
            printf("Undefined type '%s'.\n", $3.str);
        }

        if($4.isInit){
            if(intaux != TY_BYTE){
                err_printFatalError("Can not initialize not BYTE var. Not implemented yet.");
            }
            sy_addi($1.str, intaux, 0,0,1,$4.intval,NULL );
        }else{
            sy_add($1.str, intaux, 0,0 );
        }
	}
	;
VarDeclAssig:
	/* empty */ {$$.isInit = 0;}
	| T_ASSIGNMENT T_NUMBER {$$.intval = $2.intval; $$.floatval = $2.floatval; $$.isInit = 1;}
	;

System:
	T_SYSTEM T_ID
		DeviceList
	T_END_SYSTEM
	;

DeviceList:
	Device DeviceList
	| Device
	;

Device:
	T_DEVICE T_ID T_TWO_POINTS T_ID {sprintf(straux3,"%s", $2.str);}
		ResourceList
	T_END_DEVICE
	| T_DEVICE T_ID T_TWO_POINTS T_ID  T_OP T_CP {sprintf(straux3,"%s", $2.str);}
		ResourceList
	T_END_DEVICE
	;

ResourceList:
	ResourceList Resource
	| Resource
	;

Resource:
	T_RESOURCE T_ID T_TWO_POINTS T_ID T_OP T_CP {sprintf(straux2, "%s", $2.str); ic_openxml(straux3, straux2);}
		FbsListContainer
		EventConnListContainer
		DataConnListContainer
	T_END_RESOURCE {ic_closexml();}
	;

FbsListContainer:
	T_FBS
		FbsList
	T_END_FBS
	;

FbsList:
	FbsList FbsDeclaration
	| FbsDeclaration
	;

FbsDeclaration:
	T_ID T_TWO_POINTS T_ID T_SEMICOLON { ic_newInstance($1.str, $3.str, NULL, straux3, straux2); /*printf("instance %s, %s\n", $1.str, $3.str);*/ }
	| T_ID T_TWO_POINTS T_ID T_OP {alg_reset(); sprintf(straux, "%s", $3.str);} ConstAssigList T_CP T_SEMICOLON
        {
            sprintf(straux,"_init_%s_%s_%s",straux3,straux2,$1.str);
            alg_createAsmFile(straux);
            /*printf("instance %s, TYPE:%s, INIT:%s, RES:%s, DEV:%s\n", $1.str, $3.str, straux,straux2,straux3);*/
            ic_newInstance($1.str, $3.str, straux,  straux3, straux2);
            }
	;

ConstAssigList:
	ConstAssigList ConstAssig
	| ConstAssig
	;
ConstAssig:
	T_ID T_ASSIGNMENT T_NUMBER T_SEMICOLON {
        alg_gen(I_CONST, $3.intval);
        alg_gen(I_STORE, dev_getVarPos($1.str, straux));

        }
	;

EventConnListContainer:
	T_EVENT_CONNECTIONS {setConEv = 1;}
		ConnectionList
	T_END_CONNECTIONS
	;

DataConnListContainer:
	T_DATA_CONNECTIONS {setConEv = 0;}
		ConnectionList
	T_END_CONNECTIONS
	;

ConnectionList:
	ConnectionList Connection
	| Connection
	;
Connection:
	T_ID T_POINT T_ID T_TO T_ID T_POINT T_ID T_SEMICOLON
        {

       /* printf("connection %s.%s to %s.%s\n", $1.str, $3.str, $5.str, $7.str);*/
        ic_newConnection($1.str, $3.str, $5.str, $7.str, straux3, straux2);
        }
	;


/* ST Algorithms */
AlgorithmList:
	/* */
	| AlgorithmList Algorithm
	/*| Algorithm*/
	;

Algorithm:
	T_ALGORITHM T_ID T_IN T_ID T_TWO_POINTS {sy_add($2.str, 0, 1,0);}
		StatementList
	T_END_ALGORITHM {
        alg_gen(I_RET,0);

       /* alg_reset();*/
        }
	;

StatementList:
	/* empty */
	| StatementList Assignment
	| StatementList If_stat
	| StatementList While_stat
	| StatementList Call_stat T_SEMICOLON
	| StatementList AsmBlock
	;

AsmBlock:
	T_ASM AsmCode T_END_ASM{
		asm_backpath();
	}
	;

AsmCode:
	/* */
	| AsmCode Instruction
	;

Instruction:
	  T_LOAD AsmIdNum {
		alg_gen(I_LOAD, $2.intval);
	  }
	| T_CONST T_NUMBER{
		alg_gen(I_CONST, $2.intval);
	  }
	| T_STORE AsmIdNum {
		alg_gen(I_STORE, $2.intval);
	  }

    | AsmIf T_GOTO  AsmIdNumGoto  {
		/* asm_addLabelCall($3.str, alg_newLabel());
		alg_gen(I_IF, 0); */
		if($3.intval != -1){
            alg_gen($1.intval, $3.intval);
		}else{
            alg_gen($1.intval, 0);
		}
	  }
	| T_NISND {
		alg_gen(I_NISND, 0);
	  }
    | T_OR {alg_gen(I_OR,0);}
	| T_NIRCV {
		alg_gen(I_NIRCV, 0);
	  }
	/*| T_GOTO T_ID {
		asm_addLabelCall($2.str, alg_newLabel());
		alg_gen(I_GOTO, 0);
	  }*/
    | T_GOTO AsmIdNumGoto {

		if($2.intval != -1){
            alg_gen(I_GOTO, $2.intval);
		}else{
            alg_gen(I_GOTO, 0);
		}
	  }
	| T_ID T_TWO_POINTS {
		asm_addLabel($1.str, alg_newLabel());
	  }
	;

AsmIf:
    T_IF {$$.intval = I_IF;}
    | T_IFEQ {$$.intval = I_IFEQ;}
    ;

AsmIdNumGoto:
    T_ID {asm_addLabelCall($1.str, alg_newLabel()); $$.intval = -1;}
	| T_NUMBER {$$.intval = $1.intval;}
	| T_ADD T_NUMBER {$$.intval = alg_newLabel() + $2.intval;}
	;

AsmIdNum:
	T_ID {$$.intval = sy_getPos($1.str);}
	| T_NUMBER
	| T_ADD T_NUMBER {$$.intval = alg_newLabel() + $2.intval;}
	;

Call_stat:
	T_BI_SET_REG T_OP Expr T_COMA Expr T_CP  {
		alg_gen(I_ARSTORE, 0);
	}
	| T_BI_GET_REG T_OP Expr T_CP  {
		alg_gen(I_ARLOAD, 0);
		$$.type = TY_BYTE;
	}
	| T_BI_GET_REG_REAL T_OP Expr T_CP  {
		alg_gen(I_ARLOAD, TY_REAL);
		$$.type = TY_REAL;
	}
	;


While_stat:
	T_WHILE Expr T_DO
	StatementList T_END_WHILE T_SEMICOLON
	;

/*
N:  {$$.listav = listd_create(); listd_append($$.listav, alg_getNextPos());
    alg_gen(I_GOTO, 0);
    }
    ;
*/

/*
If_stat:
    T_IF If_format
    ;

If_format:
         Expr T_THEN M StatementList T_END_IF T_SEMICOLON{
            alg_backpathAll($1.listav, $3.label);
            alg_backpathAll($1.listaf, alg_newLabel());
         }
        |  Expr T_THEN M StatementList N T_ELSE M StatementList T_END_IF T_SEMICOLON{
            alg_backpathAll($1.listav, $3.label);
            alg_backpathAll($1.listaf, $7.label);
            alg_backpathAll($5.listav, alg_newLabel());
         }
       // |  Expr T_THEN M StatementList T_ELSIF If_format
        ;
*/

If_stat:
	T_IF Expr T_THEN
	{
        alg_gen(I_IF,alg_getNextPos()+2);
        pinsert(alg_getNextPos());
        alg_gen(I_GOTO, 0);
	 }
	  StatementList
	IFContinue
	;

IFContinue:
	T_END_IF T_SEMICOLON {alg_backpath(pget(),alg_getNextPos());}
	| T_ELSE {
            alg_backpath(pget(),alg_getNextPos()+1);
			pinsert(alg_getNextPos());
            alg_gen(I_GOTO, 0);



        }
     	StatementList  T_END_IF T_SEMICOLON
     	{alg_backpath(pget(),alg_getNextPos());}
	| T_ELSIF  {
		/*pinsert(alg_getNextPos());*/

        alg_backpath(pget(),alg_getNextPos()+1);
        alg_gen(I_GOTO, 0);
	}
	Expr T_THEN{
        alg_gen(I_IF,alg_getNextPos()+2);
        pinsert(alg_getNextPos());
        alg_gen(I_GOTO, 0);
	 }
	 StatementList  IFContinue
	;



Assignment:
	  T_ID T_ASSIGNMENT Expr  T_SEMICOLON {
        if(sy_getType($1.str)!=$3.type){
            //err_printWarm("Assignment of differents types.");
            alg_gen(I_CONV,$3.type <<8|sy_getType($1.str));
        }
            if(expr_postfix == 0){
                alg_gen(I_STORE, getTypeSize(sy_getType($1.str))<<8 | sy_getPos($1.str));
            }
        }

	;




M:
    /* empty */ {$$.label = alg_newLabel();}
    ;
/*
Expression: Expr {printf("Evaluated: %s\n", $1.str);};*/
Expr:
	Logical_Expr

	;

Logical_Expr:
	  Logical_Expr T_OR M Logical_Expr_p2 {

            alg_gen(I_OR,$1.type<<8 | $3.type);
            $$.type = TY_BYTE;




//			printf("%s %s %s---\n", $1.str, $4.str, "|");
			$$.str = malloc(sizeof(char)*(strlen($1.str)+strlen($4.str)+2) );
			sprintf($$.str, "%s%s%s", $1.str, $4.str, "|");

	  }
	| Logical_Expr_p2
	;

Logical_Expr_p2:
	  Logical_Expr_p2 T_AND M Logical_Expr_p1 {

            alg_gen(I_AND,$1.type<<8 | $3.type);
            $$.type = TY_BYTE;

		//if(expr_postfix == 1){
			//printf($$.str, "%s %s %s\n", $1.str, $4.str, "&");
			$$.str = malloc(sizeof(char)*(strlen($1.str)+strlen($4.str)+2) );
			sprintf($$.str, "%s%s%s", $1.str, $4.str, "&");
		//}else{

		//}
	  }
	| Logical_Expr_p1
	;

Logical_Expr_p1:
	 /* Logical_Expr_p1*/ /*T_NOT Relational_Expr {

        //$$.listaf = $2.listav; $$.listav = $2.listaf;

		//if(expr_postfix == 1){
			$$.str = malloc(sizeof(char)*(strlen($2.str)+2) );
			sprintf($$.str, "%s%s", "!",$2.str);
		//}else{

		//}
	  }*/
	| Relational_Expr
	;

Relational_Expr:
	  Relational_Expr Relational_Operator Arithmetic_Expr {
        if(expr_postfix == 0){
		/*
            $$.listav = listd_create();
            listd_append($$.listav, alg_getNextPos());
            $$.listaf = listd_create();
            listd_append($$.listaf, alg_getNextPos()+1);
            alg_gen($2.intval, 0 );
            alg_gen(I_GOTO, 0);
			*/
			alg_gen($2.intval,$1.type<<4 | $3.type);
			$$.type = TY_BYTE;
        }

	  }
	| Arithmetic_Expr {
        $$.listav = listd_create();
        $$.listaf = listd_create();
	}
	;

Arithmetic_Expr:
	  Arithmetic_Expr T_ADD Arithmetic_Expr_p1 {
        //if(expr_postfix == 0)
        //    alg_gen(I_ADD, $1.type<<4 | $3.type );
        $$.type = operationResultType($1.type,$3.type);
        if($$.type != $1.type){
            alg_gen(I_ADD, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
        }else{
            if($$.type != $3.type){
                alg_gen(I_ADD, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
            }else{
                alg_gen(I_ADD, ($1.type<<4 | $3.type) );
            }
        }
        }

	| Arithmetic_Expr T_SUB Arithmetic_Expr_p1 {/*if(expr_postfix == 0) alg_gen(I_SUB, $1.type<<4 | $3.type );  $$.type = operationResultType($1.type,$3.type);*/
        $$.type = operationResultType($1.type,$3.type);
        if($$.type != $1.type){
            alg_gen(I_SUB, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
        }else{
            if($$.type != $3.type){
                alg_gen(I_SUB, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
            }else{
                alg_gen(I_SUB, ($1.type<<4 | $3.type) );
            }
        }

	}
	| Arithmetic_Expr_p1
	;

Arithmetic_Expr_p1:
	  Arithmetic_Expr_p1 T_MUL Factor { /*if(expr_postfix == 0) alg_gen(I_MUL, $1.type<<4 | $3.type ); $$.type = operationResultType($1.type,$3.type);  */

	    $$.type = operationResultType($1.type,$3.type);
        if($$.type != $1.type){
            alg_gen(I_MUL, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
        }else{
            if($$.type != $3.type){
                alg_gen(I_MUL, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
            }else{
                alg_gen(I_MUL, ($1.type<<4 | $3.type)&0xFF );
            }
        }


	  }
	| Arithmetic_Expr_p1 T_DIV Factor { /*if(expr_postfix == 0) alg_gen(I_DIV, $1.type<<4 | $3.type ); $$.type = operationResultType($1.type,$3.type); */

	  $$.type = operationResultType($1.type,$3.type);
        if($$.type != $1.type){
            alg_gen(I_DIV, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
        }else{
            if($$.type != $3.type){
                alg_gen(I_DIV, (1<<15)| ($1.type<<12) | ($$.type<<8) | ($1.type<<4 | $3.type) );
            }else{
                alg_gen(I_DIV, ($1.type<<4 | $3.type) );
            }
        }

    }
	| Factor
	;

Factor:

	  T_NUMBER
	  {
        if($1.type == TY_BYTE){
            alg_gen(I_CONST, $1.intval&0xFF );
        }else{
            //alg_gen(I_CONST, $1.intval>>8 );
            //alg_gen(I_CONST, $1.intval&0xFF );
            alg_gen(I_CONST2, $1.intval&0xFFFF );
        }
        $$.type = $1.type;
	  }
    | T_NUMBER_REAL {
        $$.type = TY_REAL;
        float_temp.f = $1.floatval;
        //printf("Float=%X\n",float_temp.b[3]);
        alg_gen(I_CONST2, ((float_temp.b[3]<<8 & 0xFF00) | (float_temp.b[2]&0xFF))&0xFFFF );
        alg_gen(I_CONST2, ((float_temp.b[1]<<8 & 0xFF00) | (float_temp.b[0]&0xFF))&0xFFFF );
        }
	| T_OP Expr T_CP
        {
        $$.type = $2.type;
        if(expr_postfix == 0){
		/*
        $$.listaf = $2.listaf;
        $$.listav = $2.listav;
		*/

        }
        $$.str = malloc(sizeof(char) * strlen($2.str)+1); strcpy($$.str, $2.str);}
	/*| T_SUB Factor {printf("WARN 25");}*/
	| T_NOT Factor {alg_gen(I_NOT, 0);}
	| T_ID {$$.str = malloc(sizeof(char) * 5);
        $$.type = sy_getType($1.str);
            $$.str[0] = '\0';
            /*sprintf($$.str,"%s",  $1.str)*/;
            sprintf($$.str,"E%d",  22 );
           // if(expr_postfix == 0){

                //alg_gen(I_LOAD, sy_getPos($1.str) );
                alg_gen(I_LOAD, getTypeSize(sy_getType($1.str))<<8 | sy_getPos($1.str));
                if(in_evt){
                    alg_gen(I_CONST,0);
                    alg_gen(I_STORE, sy_getPos($1.str));

                }

         //   }
		}
    | Call_stat
	;

Relational_Operator:
	  T_GT {$$.intval = I_GT;}
	| T_GE {$$.intval = I_GE;}
	| T_LT {$$.intval = I_LT;}
	| T_LE {$$.intval = I_LE;}
	| T_EQ {$$.intval = I_EQ;}
	;

%%




int yywrap()
{
	return 1;
}

