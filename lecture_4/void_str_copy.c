
#include <stdio.h>

#define MAX_LEN     (100)

//Create void function that copies one string to another

void str_cpy(char *str_sorce, char *str_dest);

int main()
{
    char str1[50] = "Source";
    char str2[50] = "Destination";
    
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    
    str_cpy(str1, str2);
    printf("After copy:\n");
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    
    return 0;
}

/**
 * Copy C-string from source to destination
 * @note    Copy until string termination '\0' or 
 *          exceeds MAX_LEN
 * @param   str_sorce: pointer to source string
 * @param   str_dest: pointer to destination string
 * @retval  None
 */
void str_cpy(char *str_sorce, char *str_dest)
{
    int cnt;
    for (cnt = 0; str_sorce[cnt] != '\0' && cnt < MAX_LEN; cnt++) {
        *(str_dest + cnt) = *(str_sorce + cnt);
    }
    *(str_dest + cnt) = '\0';
}
