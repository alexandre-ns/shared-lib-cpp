/*#ifndef LIBCPP_H
#define LIBCPP_H

void processCsv(const char csv[], const char selectedColumns[], const char rowFilterDefinitions[]);
void processCsvFile(const char csvFilePath[], const char selectedColumns[], const char rowFilterDefinitions[]);

#endif*/
#ifndef LIBCPP_H
#define LIBCPP_H

#ifdef __cplusplus
extern "C" {
#endif


void processCsv(const char csv[], const char selectedColumns[], const char rowFilterDefinitions[]);
void processCsvFile(const char csvFilePath[], const char selectedColumns[], const char rowFilterDefinitions[]);

#ifdef __cplusplus
}
#endif

#endif // MATH_FUNCTIONS_H