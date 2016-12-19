/**
 * Copyright © 2016 Ashutosh Grewal. All rights reserved.
 * @file array_list.h
 *
 * @author Ashutosh Grewal
 * @date 12/17/16.
 *
 * @brief Header file containing APIs to the array_list data structure
 * and some common data structures definition and declarations.
 */


#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

typedef enum bool{
    FALSE,
    TRUE
} boolean;

typedef struct array_list_s array_list_t;

array_list_t *create_array_list (void);
boolean add_to_array_list (array_list_t *, void *, unsigned int);
boolean delete_from_array_list (array_list_t *, unsigned int);
boolean set_in_array_list (array_list_t *, void *, unsigned int);
boolean get_from_array_list (array_list_t *, void **, unsigned int);
void destroy_array_list (array_list_t *);

#endif /* ARRAY_LIST_H */
