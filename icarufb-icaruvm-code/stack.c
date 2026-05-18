/************************************************************************
    Copyright 2015 Leandro Israel Pinto
	
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
************************************************************************/

#include "stack.h"

int1 stk_push(STACK *s, int8 val)
{
    if(s->p >= STACK_SIZE)
    {
        return 0;
    }
    s->data[s->p] = val;
    s->p++;
    return 1;
}
int1 stk_pop(STACK *s, int8 *val)
{
    if(s->p == 0)
    {
        return 0;
    }
    s->p--;
    *val = s->data[s->p];
    return 1;
}
int1 stk_init(STACK *s)
{
    s->p = 0;
    return 0;
}
