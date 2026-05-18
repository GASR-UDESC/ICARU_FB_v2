/**
    Copyright 2014 Leandro Israel Pinto
	
	This file is part of ICARU_FB.

    ICARU_FB is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ICARU_FB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ICARU_FB.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>

#include "instset.h"

char * instText(char i, char *t)
{
    i = i & 0xFF;
    switch(i)
    {
    case I_DROP:
        sprintf(t, "DROP");
        break;
    case I_ADD:
        sprintf(t, "ADD");
        break;
    case I_SUB:
        sprintf(t, "SUB");
        break;
    case I_MUL:
        sprintf(t, "MUL");
        break;
    case I_DIV:
        sprintf(t, "DIV");
        break;
    case I_MOD:
        sprintf(t, "MOD");
        break;
    case I_AND: //depr
        sprintf(t, "AND");
        break;
    case I_OR: //depr
        sprintf(t, "OR");
        break;
    case I_NOT:
        sprintf(t, "NOT");
        break;
    case I_RET:
        sprintf(t, "RET");
        break;
    case I_CP2:
        sprintf(t, "CP2");
        break;
    case I_ALOAD:
        sprintf(t, "ALOAD");
        break;
    case I_CONST:
        sprintf(t, "CONST");
        break;
    case I_RETV:
        sprintf(t, "RETV");
        break;
    case I_ALLOC:
        sprintf(t, "ALLOC");
        break;
    case I_IF:
        sprintf(t, "IF");
        break;
    case I_IFEQ:
        sprintf(t, "IFEQ");
        break;
    case I_IFGT:
        sprintf(t, "IFGT");
        break;
    case I_IFLT:
        sprintf(t, "IFLT");
        break;
    case I_IFGE:
        sprintf(t, "IFGE");
        break;
    case I_IFLE:
        sprintf(t, "IFLE");
        break;
    case I_IFNE:
        sprintf(t, "IFNE");
        break;
    case I_STORE:
        sprintf(t, "STORE");
        break;
    case I_LOAD:
        sprintf(t, "LOAD");
        break;
    case I_GOTO:
        sprintf(t, "GOTO");
        break;
    case I_CALL:
        sprintf(t, "CALL");
        break;
    case I_CALLP:
        sprintf(t, "CALLP");
        break;
    /*case I_START:
        break;*/
    case I_BSET:
        sprintf(t, "BSET");
        break;
    case I_BCLR:
        sprintf(t, "BCLR");
        break;
    case I_ARSTORE:
        sprintf(t, "ARSTORE");
        break;
    case I_ARLOAD:
        sprintf(t, "ARLOAD");
        break;
    case I_NISND:
        sprintf(t, "NISND");
        break;
    case I_NIRCV:
        sprintf(t, "NIRCV");
        break;
	case I_GT:
        sprintf(t, "GT");
        break;
	case I_GE:
        sprintf(t, "GE");
        break;
	case I_LT:
        sprintf(t, "LT");
        break;
	case I_LE:
        sprintf(t, "LE");
        break;
	case I_EQ:
        sprintf(t, "EQ");
        break;
	case I_NE:
        sprintf(t, "NE");
        break;
    case I_CONST2:
        sprintf(t, "CONST2");
        break;
    case I_CONV:
        sprintf(t, "CONV");
        break;
    default:
		sprintf(t, "(null)");
        printf("(instset.h)unrecognized instruction '%X'\n", ((int)i) & 0xFF);
        //      exit(0);
        break;
    }
    return t;
}


