#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <set>

//#include "libcsv.h"

extern "C" {
    /*void processCsv(const char csv[], const char selectedColumns[], const char rowFilterDefinitions[]);
    void processCsvFile(const char csvFilePath[], const char selectedColumns[], const char rowFilterDefinitions[]);
}*/

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
        //std::string elem;
        //std::istringstream tokenStream(s);
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
        

        /*while (std::getline(split(line, ','), line)) {
        // Dividir cada linha por vírgula e adicionar ao vetor de dados
            data.push_back(split(line, ',')); //linha é o parametro "s" da função split
        }

        for (size_t i = 0; i < split(csv, '\n').size(); ++i) {
           //std::cout << words[i] << std::endl;
            data.push_back(split(line, ','));
        }*/

        for (std::vector<std::string>::iterator it = linesCsv.begin(); it != linesCsv.end(); ++it) {
            //std::cout << *it << std::endl;
            std::vector<std::string> temp = split(*it, ',');
            std::smatch match;

            for (int i = 0; i < temp.size(); ++i) {
                //std::cout << temp[i] << std::endl;
                if (std::regex_match(temp[i], match, pattern)) {
                    vectorHeaderscsv.push_back(match[1]);
                    //std::cout << match[0] << std::endl;

                }
            }
            if (!(std::regex_match(temp[0], match, pattern))) {
                data.push_back(temp);
            }


            /*for (int i = 0; i < temp.size(); ++i) {
                std::cout << "[" << temp[i] << "] ";
            
                if (std::regex_match(temp[i], match, pattern)) {
                    vectorHeaders.push_back(temp[i]);
                    //std::cout << std::endl;
                } else {
                    data.push_back(split(*it, ','));
                    //std::cout <<  << std::endl;
                }
            }*/
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
        //std::set<int> vectorLinesResult;
        //inserir todas as linhas na variavel uniqueNumbers
        for (int i = 0; i < numRows; ++i) {
            vectorLinesResult.insert(i);
        }
        for (int i = 0; i < numRows_filters; ++i) {


                std::cout << "[" << result_filters[i][0] << "]\n";
                //std::cout << "    [" << result_filters[i][SIMBOL_FILTER] << "]\n";
                //std::cout << "    [" << result_filters[i][NUMBER_FILTER] << "]\n";
                

                /*if (vectorLinesResult.empty()) {
                    std::cout << "O conjunto está vazio." << std::endl;
                } else {
                    std::cout << "O conjunto não está vazio." << std::endl;
                }*/
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
                        std::cerr << "      Operador inválido" << std::endl;
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
            //std::cout << temp[i] << std::endl;
            if (std::regex_match(selectedHeaders[i], match, pattern)) {
                selectedvectorHeaders.push_back(match[1]);
                //std::cout << match[0] << std::endl;

            }
        }

        for (int i = 0; i < selectedvectorHeaders.size(); ++i) {
            std::cout << "*[" << selectedvectorHeaders[i] << "]* ";
        }
        std::cout << std::endl;


        /*for (int i = 0; i < data.size(); ++i) {
            std::cout << "[" << selectedvectorHeaders[i] << "] ";
        }*/
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
        //std::cout << "Hello from the shared|  teste de alteração" << std::endl;
        //_________________________________________________________________________________________________
        //Código de split para pegar strings e separar usando delimitador
        std::vector<std::string> selectedvectorHeaders;
        std::vector<std::string> selectedHeaders = split(selectedColumns, ',');
        std::regex pattern(R"(header(\d+))");
        /*delimiter=",";
        s="string";

        std::vector<std::string> tokens; //vetor de strings
        std::string token;  //string temporária, cada parte extraida da string ou arquivo analizado
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;*/
        //std::cout << selectedColumns << std::endl;
        //std::cout << "\n\n" << std::endl;


        //_________________________________________________________________________________________________
        //Open file csv
        std::ifstream file(csvFilePath);
        if (!file.is_open()) {
            std::cerr << "Could not open the file!" << std::endl;
        }

        //_________________________________________________________________________________________________
        //declara uma variavel que será usada como linha
        std::string line;

        //declara a matriz que vai armazenar o csv inteiro
        std::vector<std::vector<std::string>> data;

        while (std::getline(file, line)) {
        // Dividir cada linha por vírgula e adicionar ao vetor de dados
            data.push_back(split(line, ',')); //linha é o parametro "s" da função split
        }

        file.close();
        //_________________________________________________________________________________________________
        //cria um vetor vectorselectedColumns com cada coluna
        std::vector<std::string> vectorselectedColumns= split(selectedColumns, ',');
        /*for (const auto &row : vectorselectedColumns) { //exibe o array com as colunas selecionadas
            std::cout << row << " ";
        }
        std::cout << "\n" << std::endl;*/


        //_________________________________________________________________________________________________
        //teste da função que retorna matriz de filtros
        //std::cout << rowFilterDefinitions << std::endl;
        //std::cout << "\n\n" << std::endl;
        std::vector<std::vector<std::string>> result_filters = filters(rowFilterDefinitions, '\n');


        for (const auto &row : result_filters) {
            for (const auto &col : row) {
                std::cout << "[" << col << "] ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n" << std::endl;
        int numRows_filters = result_filters.size();





        //_________________________________________________________________________________________________
        //implementação de filtros

        //define as dimensões da matriz csv
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



        //FILTRO DE FATO
        //const int NUMBER_HEADER = 0;
        const int SIMBOL_FILTER = 1;
        const int NUMBER_FILTER = 2;
        std::set<int> vectorLinesResult;

        //inserir todas as linhas na variavel uniqueNumbers
        for (int i = 0; i < numRows; ++i) {
            vectorLinesResult.insert(i);
        }

        for (int num : vectorLinesResult) {
            std::cout << num << " ";
        }
        std::cout << "\n" << std::endl;
        for (int i = 0; i < numRows_filters; ++i) {


                std::cout << "[" << result_filters[i][0] << "]\n";
                //std::cout << "    [" << result_filters[i][SIMBOL_FILTER] << "]\n";
                //std::cout << "    [" << result_filters[i][NUMBER_FILTER] << "]\n";
                

                /*if (vectorLinesResult.empty()) {
                    std::cout << "O conjunto está vazio." << std::endl;
                } else {
                    std::cout << "O conjunto não está vazio." << std::endl;
                }*/
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
                        std::cerr << "      Operador inválido" << std::endl;
                        ++j;
                    }



                }

        }
        //_________________________________________________________________________________________________

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
            //std::cout << temp[i] << std::endl;
            if (std::regex_match(selectedHeaders[i], match, pattern)) {
                selectedvectorHeaders.push_back(match[1]);
                //std::cout << match[0] << std::endl;

            }
        }

        for (int i = 0; i < selectedvectorHeaders.size(); ++i) {
            std::cout << "*[" << selectedvectorHeaders[i] << "]* ";
        }
        std::cout << std::endl;


        /*for (int i = 0; i < data.size(); ++i) {
            std::cout << "[" << selectedvectorHeaders[i] << "] ";
        }*/
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