#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <cstring>
#include <cstdlib>
#include "libcpp.h"

extern "C" {


    std::vector<std::string> split(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::vector<std::vector<std::string>> filters(const std::string &string_filters, char delimiter){
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> header_filter= split(string_filters, delimiter);
        

        std::regex pattern(R"(header(\d+)(<=|>=|>|<|=)(\d+))");
        std::smatch matches;

        for (const auto& str : header_filter) {
            if (std::regex_match(str, matches, pattern) && matches.size() == 4) {
                std::vector<std::string> row;
                row.push_back(matches[1].str()); // X
                row.push_back(matches[2].str()); // C
                row.push_back(matches[3].str()); // N
                result.push_back(row);
            }
        }

        return result;
    }


    void processCsv(const char csv[], const char selectedColumns[], const char rowFilterDefinitions[]){
        std::cout << " [[[[ processCsv ]]]] \n" << std::endl;

        std::vector<std::vector<std::string>> data;
        std::vector<std::string> linesCsv = split(csv, '\n');
        std::vector<std::string> vectorHeaderscsv;
        std::vector<std::string> selectedvectorHeaders;
        std::vector<std::string> selectedHeaders = split(selectedColumns, ',');
        std::string line;
        std::regex pattern(R"(header(\d+))");
        std::vector<std::vector<std::string>> matrixFinalResult;


        for (std::vector<std::string>::iterator it = linesCsv.begin(); it != linesCsv.end(); ++it) {
            std::vector<std::string> temp = split(*it, ',');
            std::smatch match;

            for (int i = 0; i < temp.size(); ++i) {
                if (std::regex_match(temp[i], match, pattern)) {
                    vectorHeaderscsv.push_back(match[1]);

                }
            }
            if (!(std::regex_match(temp[0], match, pattern))) {
                data.push_back(temp);
            }
        }

        int numRows = data.size();
        std::cout << "Number of rows: " << numRows << std::endl;
        if (!data.empty()) {
            int numCols = data[0].size();
            std::cout << "Number of columns: " << numCols << std::endl;
            
        }
        int numCols = data[0].size();
        
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cout << "[" << data[i][j] << "] ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n" << std::endl;

        for (int i = 0; i < vectorHeaderscsv.size(); ++i) {
            std::cout << "[" << vectorHeaderscsv[i] << "] ";
        }
        std::cout << std::endl;

        std::set<int> vectorLinesResult;


        std::vector<std::string> vectorselectedColumns= split(selectedColumns, ',');
        std::vector<std::vector<std::string>> result_filters = filters(rowFilterDefinitions, '\n');
        int numRows_filters = result_filters.size();

        const int SIMBOL_FILTER = 1;
        const int NUMBER_FILTER = 2;
        for (int i = 0; i < numRows; ++i) {
            vectorLinesResult.insert(i);
        }
        for (int i = 0; i < numRows_filters; ++i) {
                std::cout << "[" << result_filters[i][0] << "]\n";
                std::set<int>::iterator j = vectorLinesResult.begin();
                while (j != vectorLinesResult.end()) {

                    std::cout << "      [" << data[*j][ std::stoi(result_filters[i][0])-1] << "] " << result_filters[i][SIMBOL_FILTER] << result_filters[i][NUMBER_FILTER] << " ";

                    if (result_filters[i][SIMBOL_FILTER] == ">"){
                        if (!(std::stoi(data[*j][ std::stoi(result_filters[i][0])-1]) > std::stoi(result_filters[i][NUMBER_FILTER]))) {
                            std::cout << "      false\n" << std::endl;
                            j = vectorLinesResult.erase(j);
                        } else{
                            std::cout << "      true\n" << std::endl;
                            ++j;
                        }

                    } else if (result_filters[i][SIMBOL_FILTER] == "<"){
                        if (!(std::stoi(data[*j][ std::stoi(result_filters[i][0])-1]) < std::stoi(result_filters[i][NUMBER_FILTER]))) {
                            std::cout << "      false\n" << std::endl;
                            j = vectorLinesResult.erase(j);
                        } else{
                            std::cout << "      true\n" << std::endl;
                            ++j;
                        }

                    } else if (result_filters[i][SIMBOL_FILTER] == "="){
                        if (!(std::stoi(data[*j][ std::stoi(result_filters[i][0])-1]) == std::stoi(result_filters[i][NUMBER_FILTER]))) {
                            std::cout << "      false\n" << std::endl;
                            j = vectorLinesResult.erase(j);
                        } else{
                            std::cout << "      true\n" << std::endl;
                            ++j;
                        }

                    } else {
                        std::cerr << "invalid" << std::endl;
                        ++j;
                    }
                }
        }

        if (vectorLinesResult.empty()) {
            std::cout << "empty." << std::endl;
        } else {
            std::cout << "not empty" << std::endl;
            for (int num : vectorLinesResult) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }

        

        for (int i = 0; i < selectedHeaders.size(); ++i) {
            std::smatch match;
            if (std::regex_match(selectedHeaders[i], match, pattern)) {
                selectedvectorHeaders.push_back(match[1]);
            }
        }

        for (int i = 0; i < selectedvectorHeaders.size(); ++i) {
            std::cout << "*[" << selectedvectorHeaders[i] << "]* ";
        }
        std::cout << std::endl;

        std::cout << selectedColumns << std::endl;

        std::set<int>::iterator i = vectorLinesResult.begin();
        while (i != vectorLinesResult.end()) {
            
            for (const std::string& j : selectedvectorHeaders) {

                std::cout << "[" << data[*i][std::stoi(j)-1] << "] ";

            }
            std::cout << "\n" << std::endl;
            ++i;
        }
    }




    void processCsvFile(const char csvFilePath[], const char selectedColumns[], const char rowFilterDefinitions[]){
        std::vector<std::string> selectedvectorHeaders;
        std::vector<std::string> selectedHeaders = split(selectedColumns, ',');
        std::regex pattern(R"(header(\d+))");

        //Open file csv
        std::ifstream file(csvFilePath);
        if (!file.is_open()) {
            std::cerr << "error - Could not open the file!" << std::endl;
        }

        std::string line;

        //matrix csv
        std::vector<std::vector<std::string>> data;

        while (std::getline(file, line)) {
            data.push_back(split(line, ','));
        }

        file.close();

        std::vector<std::string> vectorselectedColumns= split(selectedColumns, ',');
        std::vector<std::vector<std::string>> result_filters = filters(rowFilterDefinitions, '\n');


        for (const auto &row : result_filters) {
            for (const auto &col : row) {
                std::cout << "[" << col << "] ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n" << std::endl;
        int numRows_filters = result_filters.size();

        //build filter

        //define size matrix
        int numRows = data.size();
        std::cout << "Number of rows: " << numRows << std::endl;
        if (!data.empty()) {
            int numCols = data[0].size();
            std::cout << "Number of columns: " << numCols << std::endl;
            
        }
        int numCols = data[0].size();
        
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cout << "[" << data[i][j] << "] ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n" << std::endl;



        //Filter
        const int SIMBOL_FILTER = 1;
        const int NUMBER_FILTER = 2;
        std::set<int> vectorLinesResult;

        //insert lines in uniqueNumbers
        for (int i = 0; i < numRows; ++i) {
            vectorLinesResult.insert(i);
        }

        for (int num : vectorLinesResult) {
            std::cout << num << " ";
        }
        std::cout << "\n" << std::endl;
        for (int i = 0; i < numRows_filters; ++i) {


                std::cout << "[" << result_filters[i][0] << "]\n";
                std::set<int>::iterator j = vectorLinesResult.begin();
                while (j != vectorLinesResult.end()) {

                    std::cout << "      [" << data[*j][ std::stoi(result_filters[i][0])-1] << "] " << result_filters[i][SIMBOL_FILTER] << result_filters[i][NUMBER_FILTER] << " ";

                    if (result_filters[i][SIMBOL_FILTER] == ">"){
                        if (!(std::stoi(data[*j][ std::stoi(result_filters[i][0])-1]) > std::stoi(result_filters[i][NUMBER_FILTER]))) {
                            std::cout << "      false\n" << std::endl;
                            j = vectorLinesResult.erase(j);
                        } else{
                            std::cout << "      true\n" << std::endl;
                            ++j;
                        }

                    } else if (result_filters[i][SIMBOL_FILTER] == "<"){
                        if (!(std::stoi(data[*j][ std::stoi(result_filters[i][0])-1]) < std::stoi(result_filters[i][NUMBER_FILTER]))) {
                            std::cout << "      false\n" << std::endl;
                            j = vectorLinesResult.erase(j);
                        } else{
                            std::cout << "      true\n" << std::endl;
                            ++j;
                        }

                    } else if (result_filters[i][SIMBOL_FILTER] == "="){
                        if (!(std::stoi(data[*j][ std::stoi(result_filters[i][0])-1]) == std::stoi(result_filters[i][NUMBER_FILTER]))) {
                            std::cout << "      false\n" << std::endl;
                            j = vectorLinesResult.erase(j);
                        } else{
                            std::cout << "      true\n" << std::endl;
                            ++j;
                        }

                    } else {
                        std::cerr << "invalid" << std::endl;
                        ++j;
                    }



                }

        }

        if (vectorLinesResult.empty()) {
            std::cout << "O conjunto está vazio." << std::endl;
        } else {
            std::cout << "O conjunto não está vazio." << std::endl;
            for (int num : vectorLinesResult) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < selectedHeaders.size(); ++i) {
            std::smatch match;
            if (std::regex_match(selectedHeaders[i], match, pattern)) {
                selectedvectorHeaders.push_back(match[1]);

            }
        }

        for (int i = 0; i < selectedvectorHeaders.size(); ++i) {
            std::cout << "*[" << selectedvectorHeaders[i] << "]* ";
        }
        std::cout << std::endl;

        std::cout << selectedColumns << std::endl;

        std::set<int>::iterator i = vectorLinesResult.begin();
        while (i != vectorLinesResult.end()) {
            
            for (const std::string& j : selectedvectorHeaders) {

                std::cout << "[" << data[*i][std::stoi(j)-1] << "] ";

            }
            std::cout << "\n" << std::endl;
            ++i;
        }
        }
    }