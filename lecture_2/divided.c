
#include <stdio.h>
#include <stdint.h>

#define LOW_RANGE   (1)
#define HIGH_RANGE  (500)
#define ROWS_MAX    (4)

void print_results(float divider, int low_range, int high_range);

int main ()
{
    float divider = 0;
    for (;;) {
        printf("Enter divider (float): ");
        scanf("%f", &divider);
        if (divider != 0) {
            print_results(divider, LOW_RANGE, HIGH_RANGE);
        }
        else {
            printf("ANY_NUMBER / 0 = INFINITY\n");
        }
    }
    return 0;
}

void print_results(float divider, int low_range, int high_range)
{
    unsigned int rows = 0;
    printf("\nDivide numbers from %d to %d:\n", low_range, high_range);
    for (; low_range <= high_range; low_range++) {
        for (rows = 0; rows < ROWS_MAX; rows++) {
            printf("%d/%.2f = %.2f | ", low_range, divider, ((float)low_range/divider));
        }
        printf("\n");
    }
    printf("Calculation end\n");
}