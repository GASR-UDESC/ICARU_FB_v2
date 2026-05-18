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

#ifndef _STACK_H_
#define _STACK_H_ 1

#define STACK_SIZE 35

#include "icarutypes.h"

struct stack{
    icr_uint8 data[STACK_SIZE];
    icr_uint8 p;
};

typedef struct stack STACK;

icr_int1 stk_push(STACK *s, icr_uint8 val);
icr_int1 stk_pop(STACK *s, icr_uint8 *val);
icr_int1 stk_init(STACK *s);



#endif // _STACK_H_
