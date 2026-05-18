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
#include <string.h>
#include "ospath.h"


char *pathjoin(char* destination, char* path1, char* path2)
{
    if(path1 == NULL && path2 == NULL) {
        strcpy(destination, "");;
    }
    else if(path2 == NULL || strlen(path2) == 0) {
        strcpy(destination, path1);
    }
    else if(path1 == NULL || strlen(path1) == 0) {
        strcpy(destination, path2);
    }
    else {
        char directory_separator[] = "/";
#ifdef WIN32
        directory_separator[0] = '\\';
#endif
        const char *last_char = path1;
        while(*last_char != '\0')
            last_char++;
        int append_directory_separator = 0;
        if(strcmp(last_char, directory_separator) != 0) {
            append_directory_separator = 1;
        }
        strcpy(destination, path1);
        if(append_directory_separator)
            strcat(destination, directory_separator);
        strcat(destination, path2);
    }
    return destination;
}



/*
int main(int argc, char **argv)
{
    char *d = "/usr/bin";
    char* f = "filename.txt";
    char result[strlen(d) + strlen(f) + 5];
    combine(result, d, f);
    printf("%s\n", result);
    return 0;
}
*/










