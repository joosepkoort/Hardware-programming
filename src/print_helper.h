/*
    Copyright 2016 Joosep Koort

    This file is part of riistvara_lahedane_programmeerimine_Joosep_Koort.

    riistvara_lahedane_programmeerimine_Joosep_Koort is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    riistvara_lahedane_programmeerimine_Joosep_Koort is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with riistvara_lahedane_programmeerimine_Joosep_Koort.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _PRINT_HELPER_H_
#define _PRINT_HELPER_H_

int print_ascii_tbl (FILE *stream);
int print_for_human (FILE *stream, const unsigned char *array, const int len);

#endif /* _PRINT_HELPER_H_ */
