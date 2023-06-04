#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/mathCore.h"
#define PRECISION 80000000 // 8 * 10^7

long double newtonMercatorSeries(long double x){ // returns the ln(1 + x), with x <= 1
    long double sum = 0.00;
    for(int n = 1; n < PRECISION; n++){
        sum += (pow(-1, n + 1)/n) * pow(x, n);
    }
    return sum;
}

long double * arrayLog(long double num){
    long double * array = (long double *) malloc(sizeof(long double) * 2),
                currentNum = num;
    array[0] = 0.00;
    while(currentNum > 1){
        currentNum /= 2.00;
        (array[0])++;
    }
    array[1] = currentNum;
    return array;
} // [2^n, <num_to_log>]

long double ln(long double num){
    if(num <= 1) return newtonMercatorSeries(num - 1);
    long double * array = arrayLog(num),
    ln2 = newtonMercatorSeries(1.00),
    lnNum = (array[0] * ln2) + newtonMercatorSeries(array[1] - 1);
    free(array);
    return lnNum;
}

long double logN(long double base, long double num, long double * lnBase){ // logBase(num) = ln(num)/ln(base)
    if(base == num) return 1.00;
    if(lnBase) return ln(num)/(*lnBase);
    return ln(num)/ln(base);
}

