#ifndef UTILS_H
  #define UTILS_H
  typedef struct interval INTERVAL;
  typedef struct table_data TABLE_DATA;
  INTERVAL * returnInterval();
  TABLE_DATA * returnTableData();
  long double returnTableDataBase(TABLE_DATA * tableData);
  void printIntervalData(INTERVAL * interval);
  void printTableData(TABLE_DATA * tableData);
  void pushInterval(INTERVAL * interval, long double num);
  void sumIntervalExecutionTime(INTERVAL * interval, long double time);
  void timerFunctionHandler(long double * numToReturn, 
                            long double * executionTime, 
                            long double * num, 
                            long double * base,
                            long double * lnBase,
                            long double (*ln)(long double), 
                            long double (*logN)(long double, long double, long double *));
  INTERVAL * getIntervalFromTableData(TABLE_DATA * tableData, int interval);
  long double * getIntervalData(INTERVAL * interval);
  long double getIntervalExecutionTime(INTERVAL * interval);
  int getIntervalSizeofData(INTERVAL * interval);
  void freeInterval(INTERVAL * interval);
  void freeTableData(TABLE_DATA * tableData);
#endif
