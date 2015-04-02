//
//  main.c
//  PrimeNumber
//
//  Created by Hudson Dunice on 21/03/15.
//  Copyright (c) 2015 Hudson Dunice. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int iterator = 0;
int * primes(int limit) {
    int * list, counter, i, j;

    list = (int *) malloc(limit * sizeof(int));

    #pragma omp parallel for num_threads(4) private(i, j, counter) shared(limit) schedule(dynamic, 1)
    for(i = 2; i <= limit; ++i) {
        counter = 0;

        for(j = 1; j < 10; ++j) {
            if((i % j) == 0) {
                ++counter;
            }
        }

        #pragma omp critical
        {
            if(
                i < 10 && counter <= 2
                || i >= 10 && counter < 2
            ) {
                list[iterator] = i;
                ++iterator;
            }
        }
    }

    return list;
}

void output(int * list) {
    int i;

    for(i = 0; i < iterator; ++i) {
        if(i == 0) {
            printf("%d", list[i]);
        } else {
            printf(", %d", list[i]);
        }
    }

    printf("\r\n");
}

int main(int argc, const char * argv[]) {
    int limit, * list;
    char type;
    double start, finish;

    printf("Informe o limite da lista: ");
    scanf("%d", &limit);

    printf("Informe a forma de saída (t/l/a): ");
    scanf(" %c", &type);

    start = omp_get_wtime();
    list  = primes(limit);

    switch(type) {
        case 'a':
            output(list);
            printf("Tempo de execução: %f segundos", omp_get_wtime() - start);

            break;

        case 't':
            printf("Tempo de execução: %f segundos", omp_get_wtime() - start);

            break;

        case 'l':
            output(list);

            break;
    }

    printf("\r\n");

    return 0;
}
