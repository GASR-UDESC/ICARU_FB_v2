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

#ifndef _INSTSET_H_
#define _INSTSET_H_ 1



/*
#define I_DROP	0b00000001
#define I_ADD	0b00000010
#define I_SUB	0b00000011
#define I_MUL	0b00000100
#define I_DIV	0b00000101
#define I_MOD	0b00000110
#define I_AND	0b00000111
#define I_OR	0b00001000
#define I_NOT	0b00001001
#define I_RET	0b00001010
#define I_CP2	0b00001011
//0b00001100
#define I_CONST	0b00001101
#define I_RETV	0b00001110
#define I_ALLOC	0b00001111


#define I_IFEQ	0b00010000
#define I_IFGT	0b00100000
#define I_IFLT	0b00110000
#define I_IFGE	0b01000000
#define I_IFLE	0b01010000
#define I_IFNE	0b01100000
#define I_STORE	0b01110000
#define I_LOAD	0b10000000
#define I_GOTO	0b10010000
#define I_CALL	0b10100000
#define I_START	0b10110000
#define I_BSET	0b11000000
#define I_BCLR	0b11010000
#define I_ALOAD	0b11100000
*/

#define I_DROP	1
#define I_ADD	2
#define I_SUB	3
#define I_MUL	4
#define I_DIV	5
#define I_MOD	6
#define I_AND	7
#define I_OR	8
#define I_NOT	9
#define I_RET	10
#define I_CP2	11
#define I_BSET 12
#define I_CONST	13
#define I_RETV	14
#define I_ALLOC	15

#define I_IF    16
#define I_IFEQ	17
#define I_IFGT	18
#define I_IFLT	19
#define I_IFGE	20
#define I_IFLE	21
#define I_IFNE	22
#define I_STORE	23
#define I_LOAD	24
#define I_GOTO	25
#define I_CALL	26
#define I_START	27
#define I_MSTORE	28
#define I_BCLR	29
#define I_ALOAD	30
#define I_CALLP 31

#define I_ARSTORE	32
#define I_ARLOAD    33

#define I_NISND   34
/*
    id = pop()
    data_size = pop()
    data[] = pop * data_size
*/


#define I_NIRCV    35
/*
    id = pop()
    push(data ...)
    push(data_size)

*/

#define I_GT    36
#define I_LT    37
#define I_EQ    38
#define I_GE    39
#define I_LE    40
#define I_NE    41
#define I_CONST2    42
#define I_CONV  43

/*

 ----load/store in position > 60000 will write on Process Interface
 Agora tem ARSTORE
	val = pop()
	address = pop()
	set reg[address] = val

*/



//#define I_SETG	0x01

char * instText(char i, char *t);

#endif

