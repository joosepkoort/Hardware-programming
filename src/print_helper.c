#include <stdio.h>
#include <avr/io.h>
int print_ascii_tbl (FILE *stream)
{
    for (char c = ' '; c <= '~'; c++) {
        if (!fprintf(stream, "%c ", c))    {
            return 0;
        }
    }

    //return 0;
    return fprintf(stream, "%c", (int)'\n');
}
/*

int print_for_human (FILE *stream, const unsigned char *array, const int len)
{

}
*/
