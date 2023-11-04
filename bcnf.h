#ifndef BCNF_H
#define BCNF_H

#include "header.h"
#include "output.h"

// Function to check if a set of attributes is a superkey or candidate key
bool isKey(vector<string> LHS, unordered_map<string, vector<string>> data) {

}

vector<string> fd_parser(vector<string> fds){

    vector<string> LHS;
    
    for(const auto& fd: fds)
        LHS.push_back(fd.substr(0, fd.find("->")));

    return LHS;
}

// Function to convert a dataset into BCNF
vector<Table> convertToBCNF(vector<Table> inputTables) {
    vector<Table> result;
    vector<string> LHS;

    for(const auto& inputTable : inputTables){
        LHS = fd_parser(inputTable.fundamentalDep);
    }

    return result;
}

#endif