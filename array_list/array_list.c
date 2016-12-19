/**
 * Copyright © 2016 Ashutosh Grewal. All rights reserved.
 * @file array_list.c
 * 
 * @author Ashutosh Grewal 
 * @date 12/17/16.
 *
 * @brief This file implements the array_list data structure.
 *
 * @details
 * The array list data structure is implemented as a struct with a resizeable array of void *
 * type elements. The array's capacity is maintained along with the # of elements that the array
 * currently has (capacity >= # of elements). When # of elements reaches the capacity, the array
 * is increased to 1.5 times its original size. The array inside the array list stores references
 * to the objects that are passed in. This code doesn't allocate/free memory for such objectss -
 * that is expected to be done by the user of this data structure.
 *
 * @bug No bugs are know at this point.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

#define DEFAULT_NUM_OF_ELEMENTS 2      //This ought to be 10 but then testing would take more time.

/**
 * @brief Array list data structure.
 *
 * @details
 * An array list data structure contains a resizable array, the capacity of
 * this array and the current # of elements active in the array.
 */
struct array_list_s {
    void **array;
    unsigned int capacity;
    unsigned int num_of_elements;
};

/**
 * @brief Create and initialize an array list data structure.
 *
 * @return  Pointer the memory containing the struct if successful, NULL otherwise.
 */
array_list_t *create_array_list (void)
{
    array_list_t *array_list;
    
    array_list = (array_list_t *) malloc (sizeof(array_list_t));
    
    if (array_list != NULL) {
        array_list->array = (void **) malloc (sizeof(void *) * DEFAULT_NUM_OF_ELEMENTS);
        if (array_list->array == NULL) {
            free(array_list);
            
            return NULL;
        }
        array_list->capacity = DEFAULT_NUM_OF_ELEMENTS;
        array_list->num_of_elements = 0;
    }
    
    return array_list;
}

/**
 * @brief Resize the array list to 1.5 times it's original size.
 *
 * @param[in] array_list Pointer to the array list data structure.
 *
 * @attentions
 * This implementation blows up the entire array list, if it fails to
 * allocate memory for resizing the array list.
 *
 * @return TRUE if sucessful, FALSE otherwise.
 */
static boolean resize_array_list (array_list_t *array_list)
{
    void **new_array;
    
    new_array = realloc(array_list->array, 1.5 * array_list->capacity * (sizeof(void *)));
    
    if (new_array == NULL) {
        destroy_array_list(array_list);
        
        return FALSE;
    }
    
    array_list->array = new_array;
    array_list->capacity = 1.5 * array_list->capacity;
    
    return TRUE;
}

/**
 * @brief Add an element to the array list at the specified index.
 *
 * @details
 * If you add an element to the middle of the array, the array elements
 * starting from that index are moved to the right to make space.
 *
 * @param[in] array_list Pointer to the array list data structure.
 * @param[in] new_element The element we are asked to add.
 * @param[in] index      Index at which we need to add the new element.
 * 
 * @return TRUE if sucessful, FALSE otherwise.
 */
boolean add_to_array_list (array_list_t *array_list, void *new_element, unsigned int index)
{
    if (index > array_list->num_of_elements) {
        
        return FALSE;
    }
    
    
    if (array_list->num_of_elements == array_list->capacity) {
        if (!resize_array_list(array_list)) {
            
            return FALSE;
        }
    }
    
    if (index != array_list->num_of_elements) {
        unsigned int elements_to_move;
        
        elements_to_move = array_list->num_of_elements - index;
        memmove(&array_list->array[index+1], &array_list->array[index],
                elements_to_move * sizeof(void *));
    }
    array_list->array[index] = new_element;
    array_list->num_of_elements++;
    
    return TRUE;
}

/**
 * @brief Delete an element at the specified index from the array list.
 *
 * @param[in] array_list Pointer to the array list data structure.
 * @param[in] index      Index at which we need to add the new element.
 *
 * @return TRUE if sucessful, FALSE otherwise.
 */
boolean delete_from_array_list (array_list_t *array_list, unsigned int index)
{
    if (index > array_list->num_of_elements - 1) {
        return FALSE;
    }
    
    if (index != array_list->num_of_elements - 1) {
        unsigned int elements_to_move;
        
        elements_to_move = array_list->num_of_elements - index - 1;
        memmove(&array_list->array[index], &array_list->array[index+1],
                elements_to_move * sizeof(void *));
    }
    
    array_list->num_of_elements--;
    
    return TRUE;
}

/**
 * @brief Set an element at the specified index in the array list.
 *
 * @param[in] array_list Pointer to the array list data structure.
 * @param[in] new_element The element we are asked to add.
 * @param[in] index      Index at which we need to add the new element.
 *
 * @return TRUE if sucessful, FALSE otherwise.
 */
boolean set_in_array_list (array_list_t *array_list, void *new_element, unsigned int index)
{
    if (index > array_list->num_of_elements - 1) {
        
        return FALSE;
    }
    
    array_list->array[index] = new_element;
    
    return TRUE;
}

/**
 * @brief Get an element from the specified index in the array list.
 *
 * @param[in] array_list Pointer to the array list data structure.
 * @param[out] ref_to_element Reference to memory where we will return place
 *                            the reference to the object stored in array list.
 * @param[in] index Index from where we need to obtain the requested element.
 *
 * @return TRUE if sucessful, FALSE otherwise.
 */
boolean get_from_array_list (array_list_t *array_list, void **ref_to_element, unsigned int index)
{
    if (index > array_list->num_of_elements - 1) {
        
        return FALSE;
    }
    
    *ref_to_element = array_list->array[index];
    
    return TRUE;
}

/**
 * @brief Destroy the array list by iteratively deleting all the elments
 * and freeing all the assosciated memory.
 * 
 * @param[in, out] array_list  The array list we will be deleting.
 */
void destroy_array_list (array_list_t * array_list)
{
    if (array_list->capacity) {
        free(array_list->array);
    }
    free(array_list);
}
