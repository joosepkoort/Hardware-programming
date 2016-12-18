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

#include <avr/pgmspace.h>
#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define EMPTYLCDLINE    "               "
#define STUD_NAME       "Joosep Koort"
#define WELCOME_MONTH   "Enter Month name first letter >"
#define VER_FW1         "Version: "
#define VER_FW2         " built on: "
#define VER_LIBC        "avr-libc version: "
#define VER_GCC         "avr-gcc version: "
#define MESSAGE_UPTIME  "Uptime: %lu s"
#define LCD2ROW         0x40
#define CONSOLE_HELP1   "Use backspace to delete entry and enter to confirm.\n\r"
#define CONSOLE_HELP2   "Arrow key's and del do not work currently.\n\r"
#define CON_IMPLEMENTED "Command not implemented.\n Use <help> to get help.\n"
#define CON_ARGUMENTS   "To few or to many arguments for this command\nUse <help>\n"
#define CON_CMD_IMPL    "Implemented commands:\n"
#define ACCESS          "ACCESS DENIED!"

extern PGM_P const months[];

#endif /* _HMI_MSG_H_ */


