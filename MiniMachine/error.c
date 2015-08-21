#include "error.h"
#include <stdlib.h>
void error_crash(char *sz_error)
{
    printf_s("error: %s\n",sz_error);
    exit(0);
}
void error_report(char* sz_error)
{
    printf_s("report: %s\n", sz_error);
}