
#include <stdio.h>
#include <stdint.h>

#define TEST_SIZE   (10)

const int TEST_ARR[TEST_SIZE] = {0,1,2,3,4,555,6,7,8,9};

int find_max(int *arr, int arr_size);

int main()
{
    int max_val = 0;
    printf("Test array:");
    for (int cnt = 0; cnt < TEST_SIZE; cnt++)
    {
        printf(" [%d] = %d%c", cnt, TEST_ARR[cnt], (TEST_SIZE-1 == cnt ? '\n' : ';'));
    }
    max_val = find_max(TEST_ARR, TEST_SIZE);
    printf("The biggest value is: %d\n", max_val);
    return 0;
}


int find_max(int *arr, int arr_size)
{
    int cnt = 0, buff = *arr;
    for (cnt = 0; cnt < arr_size; cnt++)
    {
        if(arr[cnt] > buff)
        {
            buff = arr[cnt];
        }
    }
    return buff;
}