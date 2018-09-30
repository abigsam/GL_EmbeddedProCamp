
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_INIT      ((int) 0)

//Create queue library based on array

int queue_init(int size);
int queue_deinit(void);
int queue_put(int val);
int queue_get(int *val);
int queue_read(int *val);

//Pointer to the queue
int *head_ptr = NULL;
int *read_ptr = NULL;
int *write_ptr = NULL;
int queue_size = 0;

/* Main */
int main()
{
    
    
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
    memset((int *)ptr, (int)0, queue_size * sizeof(int)); //Clear queue
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
    if (write_ptr >= (head_ptr + queue_size)) {
        //Check if read_ptr bigger than header (enough space for 1 element)
        if (read_ptr > head_ptr) {
            write_ptr = head_ptr;
            *write_ptr = val;
            return ((int)(read_ptr - write_ptr));
        }
        else {
            //Not enough space
            return -1;
        }
    }
    //Check if write_ptr is bigger than read_ptr
    if (write_ptr > read_ptr) {
        *write_ptr = val;
        write_ptr++;
        return ((int)(read_ptr - write_ptr));
    }
    //Check if write_ptr is less than read_ptr
    if (read_ptr > write_ptr) {
        //Check if enough space for one lement
        
    }
        
        
        //Check if write_ptr will overlap queue size
        if ((write_ptr + 1) > (head_ptr + queue_size)) {
            //If next write_ptr is bigger than queue size
            if (read_ptr != head_ptr) {
                //If read_ptr bigger than header (enough space for 1 element)
                write_ptr = head_ptr;
                *write_ptr = val;
                return ((int)(read_ptr - write_ptr));
            }
            else { //Not enough space
                return -1;
            }
        }
        else {
            //If write_ptr do not overlap queue size
            *write_ptr = val;
            write_ptr++;
            return ((int)(write_ptr - read_ptr));
        }
    }
    else if (read_ptr > write_ptr) {
        
    }
    else {
        //it equals
        //Not enough space
        return -1;
    }
    return 0;
}

/**
 * Put value to the queue
 * @param   Value
 * @retval  Number of left elements to read, '0' if queue is empty
 */
int queue_get(int *val)
{
    
    
}

/**
 * Read last value from the queue
 * @param   val: pointer to the output value
 * @retval  '0' if queue was inited
 */
int queue_read(int *val)
{
    if (read_ptr != NULL) {
        *value = *read_ptr;
        return 0;
    }
    return -1;
}
