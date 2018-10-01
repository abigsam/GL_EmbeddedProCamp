#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#define NUMBER  ((uint64_t) 10)

uint64_t factorial(uint64_t number);

int main ()
{
    printf("Factorial of %"PRId64" is %"PRId64"\n", NUMBER, factorial(NUMBER));
    return 0;
}

uint64_t factorial(uint64_t number)
{
    if (number > 1u) {
        return ( number * factorial(number-1) );
    }
    else if (1u == number) {
        return 1u;
    }
    return 0u;
}