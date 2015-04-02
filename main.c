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
#include <math.h>

int iterator = 0;
int * primes(int limit) {
    int * list, counter, i, j;
    double square = sqrt(limit);

    list = (int *) malloc(limit * sizeof(int));
    list[2] = 2;

    #pragma omp parallel for num_threads(1) private(i, j, counter) shared(limit, list, square) schedule(guided, 1)
    for(i = 3; i <= limit; i += 2) {
        counter = 0;

        for(j = 1; j < square; ++j) {
            if((i % j) == 0) {
                ++counter;
            }

            if(counter > 2) {
                break;
            }
        }

        if(counter <= 2) {
            list[i] = i;
        }
    }

    return list;
}

void output(int * list, int limit) {
    int i;

    printf("%d ", list[2]);

    for(i = 3; i < limit; i += 2) {
        if(list[i]) {
            printf("%d ", list[i]);
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
            output(list, limit);
            printf("Tempo de execução: %f segundos", omp_get_wtime() - start);
            printf("\r\n");

            break;

        case 't':
            printf("Tempo de execução: %f segundos", omp_get_wtime() - start);
            printf("\r\n");

            break;

        case 'l':
            output(list, limit);

            break;
    }

    return 0;
}
