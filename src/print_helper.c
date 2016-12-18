/*
    Copyright 2016 Joosep Koort

    This file is part of lab06_Joosep_Koort.

    lab06_Joosep_Koort is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    lab06_Joosep_Koort is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with lab06_Joosep_Koort.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include "print_helper.h"

int print_ascii_tbl (FILE *stream)
{
    for (char c = ' '; c <= '~'; c++) {
        if (!fprintf(stream, "%c ", c)) {
            return 0;
        }
    }

    return fprintf(stream, "\n");
}


int print_for_human (FILE *stream, const unsigned char *array, const int len)
{
    for (int i = 0; i < len; i++) {
        unsigned char c = array[i];

        if (c >= ' ' && c <= '~') {
            if (!fprintf(stream, "%c", c)) {
                return 0;
            }
        } else {
            if (!fprintf(stream, "\"0x%02x\"", c)) {
                return 0;
            }
        }
    }

    return fprintf(stream, "\n");
}
