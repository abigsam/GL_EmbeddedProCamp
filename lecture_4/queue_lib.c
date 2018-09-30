
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_INIT      ((int) 0)
#define QUEUE_LEN       (11)

//Create queue library based on array

int queue_init(int size);
void queue_deinit(void);
int queue_put(int val);
int queue_get(int *val);
int queue_read(int *val);
//Aux. function
void print_queue(void);

//Pointer to the queue
int *head_ptr = NULL;
int *read_ptr = NULL;
int *write_ptr = NULL;
int queue_size = 0;

/* Main */
int main()
{
    int cnt = 0;
    int temp = 0;
    int len = 0;
    //init queue
    queue_init(QUEUE_LEN);
    print_queue();
    
    //Add some values
    for(cnt = 0; cnt < 9; cnt++) {
        len = queue_put(cnt);
        if (len < 0) {
            printf("Put error\n");
            return -1;
        }
        printf("Put %d (write length = %d)\n", cnt, len);
    }
    print_queue();
    
    //Read come values
    for(cnt = 0; cnt < 3; cnt++) {
        len = queue_get(&temp);
        if (len < 0) {
            printf("Queue is empty\n");
            return -2;
        }
        printf("Get %d (read length = %d)\n", temp, len);
    }
    print_queue();
    
    //Write for overlap
    for (cnt = 0; cnt < 4; cnt++) {
        len = queue_put(cnt+9);
        if (len < 0) {
            printf("Put error\n");
            return -1;
        }
        printf("Put %d (write length = %d)\n", cnt+9, len);
    }
    print_queue();
    
    //Read until empty
    len = 1;
    while (len > 0) {
        len = queue_get(&temp);
        printf("Get %d (read length = %d)\n", temp, len);
    }
    print_queue();
    
    queue_deinit();
    
    return 0;
}


/**
 * Init queue array
 * @param   size: size of queue
 * @retval  '0' if success
 */
int queue_init(int size)
{
    int *ptr = malloc(sizeof(int) * size);
    if (ptr != NULL) {
        memset((int *)ptr, (int)0, size * sizeof(int));
        head_ptr = ptr;
        read_ptr = ptr;
        write_ptr = ptr;
        queue_size = size;
        return 0; //Success
    }
    return -1; //Fail malloc
}

/**
 * Deinit queue array
 * @param   None
 * @retval  None
 */
void queue_deinit(void)
{
    memset((int *)head_ptr, (int)0, queue_size * sizeof(int)); //Clear queue
    read_ptr = NULL;
    write_ptr = NULL;
    free(head_ptr);
}

/**
 * Put value to the queue
 * @param   Value
 * @retval  Number of free elements, '0' if queue is full, '-1' if no space
 */
int queue_put(int val)
{
    //Check if write_ptr is overlap queue
    if (write_ptr >= (head_ptr + queue_size - 1)) {
        //Check if read_ptr bigger than header (enough space for 1 element)
        if (read_ptr > head_ptr) {
            *write_ptr = val;
            write_ptr = head_ptr;
            return ((int)(read_ptr - write_ptr));
        }
        else {
            //Not enough space
            return -1;
        }
    }
    //Check if write_ptr is bigger than read_ptr
    if (write_ptr >= read_ptr) {
        *write_ptr = val;
        write_ptr++;
        return ((int)((read_ptr+queue_size)-write_ptr));
    }
    //Check if write_ptr is less than read_ptr + 1 element
    if (read_ptr > (write_ptr + 1)) {
        *write_ptr = val;
        write_ptr++;
        return ((int)(read_ptr - write_ptr));
    }
    return 0;
}

/**
 * Put value to the queue
 * @param   Value
 * @retval  Number of left elements to read, '0' if no elements left to read,
 *          '-1' if queue is empty
 */
int queue_get(int *val)
{
    //Check if queue is empty
    if (read_ptr == write_ptr) {
        return -1; //Queue is empty
    }
    //Check if read_ptr overlap queue
    if (read_ptr >= (head_ptr + queue_size - 1)) {
        *val = *read_ptr;
        read_ptr = head_ptr;
        return ((int)(write_ptr - read_ptr));
    }
    //Check if read_ptr is less than write_ptr
    if (read_ptr < write_ptr) {
        *val = *read_ptr;
        read_ptr++;
        return ((int)(write_ptr - read_ptr));
    }
    //Check if read_ptr is bigger than write_ptr
    if (read_ptr > write_ptr) {
        *val = *read_ptr;
        read_ptr++;
        return ((int)(write_ptr + queue_size - read_ptr));
    }
    return 0; //Not reachiable
}

/**
 * Read last value from the queue
 * @param   val: pointer to the output value
 * @retval  '0' if queue was inited
 */
int queue_read(int *val)
{
    if (read_ptr != NULL) {
        *val = *read_ptr;
        return 0;
    }
    return -1;
}

/**
 * Aux. function
 */
void print_queue(void)
{
    if (NULL == head_ptr) { return; }
    printf("Queue values: ");
    for (int cnt = 0; cnt < queue_size; cnt++) {
        printf("%d, ", head_ptr[cnt]);
    }
    printf("\n");
    printf("Read #%d ", (int)(read_ptr - head_ptr));
    printf("Write #%d\n", (int)(write_ptr - head_ptr));
}

