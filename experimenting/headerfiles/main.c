#include <stdio.h>
#include "complex.h"

int main()
{
    Complex test;
    test.a = 2;
    test.b = 2.8;
    printf("test=%s\n", fmtCplx(test));
}
