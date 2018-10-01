
#include <stdio.h>
#include <stdint.h>

#define STR_MAX     ((uint32_t) 40)
#define TEST_NUM    (5)

/* Test strings */
const uint8_t *test_str[TEST_NUM] = { "sdf65 34+11 *^6 +zdf +6sEf1v9",
                                      "34-*54+dfb+4 +srt*64",
                                      "asfodfvjkn  da fvieariur e hSpp IP",
                                      "23456984-*87fgn 651fdn4sdt h+4rwh+45",
                                      "jdavjn wer9835iu erjdsf09d  dfnnse0535 n u45" };

int32_t str_copy_digit(uint8_t *src, uint8_t *dest);

int main()
{
    uint32_t test_cnt = 0u;
    int32_t num_cpy = 0;
    uint8_t dest_str[STR_MAX] = {'\0'};
    
    printf("Number of test strings: %d\n", TEST_NUM);
    for (test_cnt = 0u; test_cnt < TEST_NUM; test_cnt++)
    {
        printf("Test string #%d:\n", test_cnt);
        printf("\"%s\"\n", test_str[test_cnt]);
        num_cpy = str_copy_digit(test_str[test_cnt], dest_str);
        if (num_cpy < 0)
        {
            printf("Sorce string too big", num_cpy);
        }
        else if (num_cpy > 0)
        {
            printf("Source string has %d number(s): \"%s\"", num_cpy, dest_str);
        }
        else //No digits in source string
        {
            printf("Source string do not have numbers");
        }
        printf("\n\n");
    }

    return 0;
}


int32_t str_copy_digit(uint8_t *src, uint8_t *dest)
{
    int32_t cnt_src = 0, cnt_dest = 0;
    for (cnt_src = 0, cnt_dest = 0;
         ((src[cnt_src] != NULL) && (cnt_src < STR_MAX));
         cnt_src++)
    {
        if(src[cnt_src] >= '0' && src[cnt_src] <= '9')
        {
            *(dest + cnt_dest) = *(src + cnt_src);
            cnt_dest++;
        }
    }
    dest[cnt_dest] = NULL; //Terminate destination string
    if ((src[cnt_src] != NULL) && (cnt_src >= STR_MAX))
    {
        return -1; //Source string exeed STR_MAX size
    }
    else
    {
        return cnt_dest; //Return number of chars copied to destination string
    }
}