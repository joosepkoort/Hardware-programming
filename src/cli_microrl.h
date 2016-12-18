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

#ifndef _CLI_MICROCL_H_
#define _CLI_MICROCL_H_

void read_card(void);
void add_card(const char *const *argv);
void remove_card(const char *const *argv);
void list_cards(void);
void cli_print(const char * str);
int cli_execute(int argc, const char *const *argv);
#endif /* End _CLI_MICROCL_H_ header guard */
