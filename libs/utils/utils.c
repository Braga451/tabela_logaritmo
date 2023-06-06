#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/utils.h"

struct interval{
  int sizeofData;
  long double executionTime;
  long double * data;
};

struct table_data{
  long double base;
  long double inferiorLimit;
  long double superiorLimit;
  INTERVAL * first;
  INTERVAL * second;
  INTERVAL * third;
};

long double getInferiorLimitFromTableData(TABLE_DATA * tableData){
  if(!tableData) return -1;
  return tableData->inferiorLimit;
}

long double getSuperiorLimitFromTableData(TABLE_DATA * tableData){
  if(!tableData) return -1;
  return tableData->superiorLimit;
}

void setInferiorLimitForTableData(TABLE_DATA * tableData, long double inferiorLimit){
  if(!tableData) return;
  tableData->inferiorLimit = inferiorLimit;
}

void setSuperiorLimitForTableData(TABLE_DATA * tableData, long double superiorLimit){
  if(!tableData) return;
  tableData->superiorLimit = superiorLimit;
}

long double * getIntervalData(INTERVAL * interval){
  if(!interval) return NULL;
  return interval->data;
}

long double getIntervalExecutionTime(INTERVAL * interval){
  if(!interval) return -1;
  return interval->executionTime;
}

int getIntervalSizeofData(INTERVAL * interval){
  if(!interval) return -1;
  return interval->sizeofData;
}

INTERVAL * getIntervalFromTableData(TABLE_DATA * tableData, int interval){
  if(!tableData) return NULL;
  switch(interval){
    case 1:
      return tableData->first;
    case 2:
      return tableData->second;
    case 3:
      return tableData->third;
    default:
      return NULL;
  }
  return NULL;
}

INTERVAL * returnInterval(){
  INTERVAL * interval = (INTERVAL *) malloc(sizeof(INTERVAL));
  interval->sizeofData = 0;
  interval->data = NULL;
  return interval;
}

TABLE_DATA * returnTableData(long double base){
  TABLE_DATA * tableData = (TABLE_DATA *) malloc(sizeof(TABLE_DATA));
  tableData->base = base;
  tableData->first = returnInterval();
  tableData->second = returnInterval();
  tableData->third = returnInterval();
  return tableData;
}

long double returnTableDataBase(TABLE_DATA * tableData){
  if(!tableData) return -1;
  return tableData->base;
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

void sumIntervalExecutionTime(INTERVAL * interval, long double time){
  if(!interval) return;
  interval->executionTime += time;
}

void freeInterval(INTERVAL * interval){
  if(!interval) return;
  free(interval->data);
  free(interval);
}

void freeTableData(TABLE_DATA * tableData){
  if(!tableData) return;
  freeInterval(tableData->first);
  freeInterval(tableData->second);
  freeInterval(tableData->third);
  free(tableData);
}

void printIntervalData(INTERVAL * interval){
  if(!interval) return;
  for(int x = 0; x < interval->sizeofData; x++){
    printf("%Lf ", interval->data[x]);
  }
  printf("\nExecution time: %Lf\n", interval->executionTime);
}

void printTableData(TABLE_DATA * tableData){
  if(!tableData) return;
  printIntervalData(tableData->first);
  printIntervalData(tableData->second);
  printIntervalData(tableData->third);
}

void timerFunctionHandler(long double * numToReturn, 
                          long double * executionTime, 
                          long double * num, 
                          long double * base, 
                          long double * lnBase,
                          long double (*ln)(long double), 
                          long double (*logN)(long double, long double, long double *)){
  clock_t begin = clock(), end;
  if(!base){
    *numToReturn = ln(*num);
    end = clock();
    *executionTime = (long double)(end - begin)/CLOCKS_PER_SEC;
    return;
  }
  *numToReturn = logN(*base, *num, lnBase);
  end = clock();
  *executionTime = (long double)(end - begin)/CLOCKS_PER_SEC;
}
