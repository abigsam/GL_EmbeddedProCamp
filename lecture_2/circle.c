#include <stdio.h>

#define RADIUS  (6.0)
#define PI      (3.1415)

float area(float radius);
float perimeter(float radius);

int main ()
{
    printf("Circle with radius %.2f meter(s) has:\n", RADIUS);
    printf(" >> perimeter %.2f meter(s)\n", perimeter(RADIUS));
    printf(" >> area %.2f sq. meter(s)\n", area(RADIUS));
    return 0;
}

float area(float radius)
{
    return ( PI * radius * radius );
}

float perimeter(float radius)
{
    return ( 2.0 * PI * radius );
}