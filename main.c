#include <stdio.h>
#include "libcpp.h"


//void my_function();
char** filters(const char filters[], char delimiter);
char** split( const char[] , char delimiter);
void processCsvFile(const char csvFilePath[], const char selectedColumns[], const char rowFilterDefinitions[]);
void processCsv(const char csv[], const char selectedColumns[], const char rowFilterDefinitions[]);

int main() {
  const char csvFilePath[] = "./data2.csv";
  const char csv[] = "header1,header2,header3\n1,2,3\n4,5,6\n7,8,9";
  const char selectedColumns[] = "header1,header3";
  const char rowFilterDefinitions[] = "header1>1\nheader3<10";
  //processCsvFile(csvFilePath, selectedColumns, rowFilterDefinitions);
  processCsv(csv, selectedColumns, rowFilterDefinitions);
  return 0;
}