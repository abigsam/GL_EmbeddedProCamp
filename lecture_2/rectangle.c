#include <stdio.h>

#define TO_INCH(m)  ((float)m * 39.37)

float area(float height, float weight);
float perimeter(float height, float weight);

int main ()
{
    float height = 0.0, weight = 0.0;
    float result = 0.0;
    for(;;)
    {
        printf("Enter height (in meters): ");
        scanf("%f", &height);
        printf("Enter weight (in meters): ");
        scanf("%f", &weight);
        printf("Perimeter is: %.2f inches\n", perimeter(height, weight));
        printf("Area is: %.2f sq. inches\n", area(height, weight));
    }
    return 0;
}

float area(float height, float weight)
{
    return ( TO_INCH(height) * TO_INCH(weight) );
}

float perimeter(float height, float weight)
{
    return ( 2.0 * (TO_INCH(height) + TO_INCH(weight)) );
}