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

//Some compilers don't compile in modules .o
//you need to compile all in one file.
//So we include all .c files at the end

#include "hdw.c"
#include "ram.c"
#include "disk.c"
#include "fbs.c"
#include "hdwfbs.c"
#include "stack.c"
#include "net.c"
#include "instset.c"
#include "handlenet.c"
