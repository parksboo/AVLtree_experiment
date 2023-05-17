//
//  csv.c
//  data_structure_experiment
//
//  Created by 박성부 on 2023/05/11.
//
#include <stdlib.h>
#include <string.h>
#include "csv.h"

static int idx = 0;

void remove_char(char *str, char to_remove)
{
    char *ptr = str;
    while ((ptr = strchr(ptr, to_remove)) != NULL)
    {
        memmove(ptr, ptr + 1, strlen(ptr));
    }
}

element *add_element(element *arr, element value)
{

    arr = (element *)realloc(arr, (idx + 1) * sizeof(element));
    arr[idx] = value;
    idx++;
    return arr;
}

element *read_csv(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error!! can not load file: %s\n", filename);
        exit(1);
    }

    element *arr = NULL;
    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        element value;
        char *token = strtok(line, ",");

        if (token != NULL)
        {
            remove_char(token, 'A');
            value.code = atoi(token);
            token = strtok(NULL, ",");
        }

        if (token != NULL)
        {
            strncpy(value.name, token, sizeof(value.name) - 1);
            value.name[sizeof(value.name) - 1] = '\0'; // ensure null termination
            token = strtok(NULL, ",");
        }

        if (token != NULL)
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            value.mk_capitalization = atoi(token);
            token = strtok(NULL, ",");
        }

        if (token != NULL)
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            value.price = atoi(token);
        }

        arr = add_element(arr, value);
    }

    fclose(file);
    return arr;
}

void findAndPrintarray(element *array, int code)
{
    int i = 1;
    while (array[i].code)
    {
        if (array[i].code == code)
        {
            // printf("Code: %d\n", array[i].code);
            // printf("Name: %s\n", array[i].name);
            // printf("Market capitalization: %d\n", array[i].mk_capitalization);
            // printf("Price: %d\n", array[i].price);
            return;
        }
        else
            i++;
    }

    // 코드를 찾지 못하면 메시지 출력
    printf("No node with code: %d\n", code);
}