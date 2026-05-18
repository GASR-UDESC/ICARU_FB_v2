/****

    Copyright 2014 Leandro Israel Pinto

    This file is part of IECCOMP.

    IECCOMP3 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    IECCOMP3 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with IECCOMP3.  If not, see <http://www.gnu.org/licenses/>.


****/




#include <stdio.h>
#include <stdlib.h>


#include "instset.h"
#include "algcode.h"
#include "device.h"
#include "pilha.h"

#include "errors.h"

#include "instcon.h"
#include "asmltab.h"
#include "atributos.h"
#include "iec.tab.c"

#include "ecc.h"
#include "symbols.h"



/*
extern FILE *yyin;
*/
int main(int argc, char **argv)
{
    FILE *f;

    int i;

//   lib_init();
//   sys_init();
    sy_init();
    ic_init();
    alg_init();
    alg_reset();
    dev_init();
    asm_init();
    pinit();
    if(argc < 2)
    {
        puts("iec2c input_file\n");
        exit(1);
    }

    i = 1;
    while(i < argc)
    {
        if(strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0)
        {
            i++;
            alg_setOutput(argv[i]);
            ecc_setOutput(argv[i]);
            sy_setOutput(argv[i]);
        }
        else
        {
            err_lineReset();

            //if(strstr(argv[i], "START.st")==NULL)
            //{
                f =fopen(argv[i],"r");
                //strcpy( atualarq,argv[i]);

                if(f)
                {
                    err_setFile(argv[i]);
                    yyin = f;
                    //printf("Parsing '%s'...\n", argv[i]);
                    yyparse();
                    fclose(f);
                }
                else
                {
                    printf("Invalid file: '%s'\n", argv[i]);
                }
           // }
           // else
            //{
           //     printf("Warn: START block will no be compiled. Use a standard file.\n");
           // }

        }
        i++;
    }
//   lib_print2();
//   sys_print();
//   sy_print();

    //puts("************* SUCCESS! ***************");

    return 0;
}

