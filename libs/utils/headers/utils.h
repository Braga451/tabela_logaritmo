#ifndef UTILS_H
  #define UTILS_H
  typedef struct interval INTERVAL;
  typedef struct table_data TABLE_DATA;
  INTERVAL * returnInterval();
  void pushInterval(INTERVAL * interval, long double num);
  void timerFunctionHandler(long double * numToReturn, double * executionTime, long double * num, long double * base, double (*ln)(long double), double (*logN)(long double, long double));
#endif
