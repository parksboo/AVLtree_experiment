//
//  main.c
//  data_structure_experiment
//
//  Created by 박성부 on 2023/05/11.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "csv.h"
#include "avlTree.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_csv_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int i = 1;
    element *data_array = read_csv(filename);
    Node *data_AVLtree = NULL;
    while (data_array[i].code)
    {
        data_AVLtree = insertNode(data_AVLtree, data_array[i].code, data_array[i].name, data_array[i].mk_capitalization, data_array[i].price);
        i++;
    }
    i--;
    // 범위에 해당하는 램덤한 숫자를 검색할 code로 설정

    int numCode;
    // char code[50]="A000000";
    // int numCode = atoi(&code[1]);

    clock_t start_avl, end_avl, start_array, end_array;
    double cpu_time_used4avl, cpu_time_used4array;

    start_avl = clock();
    for (int cycle = 0; cycle < 10; cycle++) // cycle < i
    {
        srand(time(0) + cycle);
        numCode = data_array[(rand() % i) + 1].code;
        findAndPrintNode(data_AVLtree, numCode);
    }
    end_avl = clock();
    cpu_time_used4avl = ((double)(end_avl - start_avl)) / CLOCKS_PER_SEC;
    // printf("Search time (in seconds) taken by the AVL tree. : %f\n", cpu_time_used4avl);

    // array를 사용하여 작업 수행
    start_array = clock();
    for (int cycle = 0; cycle < 10; cycle++) // cycle < i
    {
        srand(time(0) + cycle);
        numCode = data_array[(rand() % i) + 1].code;
        findAndPrintarray(data_array, numCode);
    }
    end_array = clock();
    cpu_time_used4array = ((double)(end_array - start_array)) / CLOCKS_PER_SEC;
    // printf("Search Time (in seconds) taken by array: %f\n", cpu_time_used4array);
    printf("%f,%f\n", cpu_time_used4avl, cpu_time_used4array); // test2 : same data size
    // printf("%d,%f,%f\n", ++i, cpu_time_used4avl, cpu_time_used4array); // test1 : diff data size
    //   할당된 메모리 해제
    free(data_array);
    freeNode(data_AVLtree);
    return 0;
}
