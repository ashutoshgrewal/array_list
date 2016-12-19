/**
 * Copyright © 2016 Ashutosh Grewal. All rights reserved.
 *
 * @file main.c
 * @author Ashutosh Grewal on 12/17/16.
 *
 * @brief This file just contains some code that uses the APIs of
 * array list data structure
 */

#include <stdio.h>
#include "array_list.h"


int main(int argc, const char * argv[]) {
    array_list_t *array_list;
    int array[5] = {1, 2, 3, 4, 5};
    unsigned int index;
    void *ref_to_object;
    
    array_list = create_array_list();
    add_to_array_list(array_list, &array[0], 0); // Array list's array will be 1
    add_to_array_list(array_list, &array[1], 0); // Array list's array will be 2, 1
    add_to_array_list(array_list, &array[2], 0); // Array list's array will be 3, 2, 1
    add_to_array_list(array_list, &array[3], 0); // Array list's array will be 4, 3, 2, 1

    index = 1;
    get_from_array_list(array_list, &ref_to_object, index);
    printf("Value at index %u is %d\n", index, *((int *)ref_to_object));
    
    delete_from_array_list(array_list, index); // Array list's array will be 4, 2, 1
    get_from_array_list(array_list, &ref_to_object, index);
    printf("Value at index %u is %d\n", index, *((int *)ref_to_object));
    
    destroy_array_list(array_list);
    return 0;
}
