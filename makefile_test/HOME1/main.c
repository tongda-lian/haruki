#include <stdio.h>
#include "my_math.h"
#include <math.h>
#include "order.h"

int main()
{
    double x, y;
    printf("input x and y:\n");
    scanf("%lf%lf", &x, &y);
    printf("x = %f, y = %f\n", x, y);
    
    double sum = 0;
    sum = add(x, y);
    printf("sum:%lf\n", sum);
    
    double result = 0;
    result = minus(x, y);
    printf("minus:%lf\n", result);
    
    result = 0;
    result = multiply(x, y);
    printf("multiply:%lf\n", result);
    
    result = 0;
    result = divide(x, y);
    printf("divide:%lf\n", result);
    
    result = 0;
    result = order(x, y);
    printf("order:%lf\n", result);
    return 0;
}
