//
//  csv.h
//  data_structure_experiment
//
//  Created by 박성부 on 2023/05/11.
//

#ifndef csv_h
#define csv_h

#include <stdio.h>

typedef struct
{
    char name[50];
    int code;
    int mk_capitalization;
    int price;
} element;

element *add_element(element *arr, element value);
element *read_csv(const char *filename);
void findAndPrintarray(element *array, int code);

#endif /* csv_h */
