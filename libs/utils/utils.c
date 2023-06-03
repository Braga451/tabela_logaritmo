#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/utils.h"

struct interval{
  int sizeofData;
  int executionTime;
  long double * data;
};

struct table_data{
  char * base;
  INTERVAL * first;
  INTERVAL * second;
  INTERVAL * third;
};

INTERVAL * returnInterval(){
  INTERVAL * interval = (INTERVAL *) malloc(sizeof(INTERVAL));
  interval->sizeofData = 0;
  interval->data = NULL;
  return interval;
}

void pushInterval(INTERVAL * interval, long double num){
  if(!interval) return;
  long double * aux = NULL;
  (interval->sizeofData)++;
  aux = (long double *) realloc(interval->data, sizeof(long double) * interval->sizeofData);
  if(!aux){
    puts("[-] Error in realloc!");
    return;
  }
  interval->data = aux;
  interval->data[interval->sizeofData - 1] = num;
}

void timerFunctionHandler(long double * numToReturn, 
                          double * executionTime, 
                          long double * num, 
                          long double * base, 
                          double (*ln)(long double), 
                          double (*logN)(long double, long double)){
  clock_t begin = clock(), end;
  if(!base){
    *numToReturn = ln(*num);
    end = clock();
    *executionTime = (double)(end - begin)/CLOCKS_PER_SEC;
    return;
  }
  *numToReturn = logN(*base, *num);
  end = clock();
  *executionTime = (double)(end - begin)/CLOCKS_PER_SEC;
}
