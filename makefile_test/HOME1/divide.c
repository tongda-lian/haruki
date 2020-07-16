#include <stdio.h>

#include "my_math.h"
double divide(double x, double y)
{
    if(y == 0)
    {
        printf("y can't be zero\n");
        return 0;
    }
    return x / y;
}
