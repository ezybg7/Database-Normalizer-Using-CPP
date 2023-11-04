#ifndef BCNF_H
#define BCNF_H

#include "header.h"
#include "output.h"
#include "nf2.h"
#include "nf3.h"

// Function to check if a set of attributes is a superkey
// bool isSuperkey(vector<string> LHS, unordered_map<string, vector<string>> data) {

// }

//left hand side of fd
vector<string> lhs_parser(const string& fd) {
    vector<string> LHS;
    istringstream stream(fd.substr(0, fd.find("->")));
    string token;

    while (getline(stream, token, ',')) {
        //remove whitespace
        size_t firstNotSpace = token.find_first_not_of(" \t\n\v\f\r");
        size_t lastNotSpace = token.find_last_not_of(" \t\n\v\f\r");

        //push into vector
        if (firstNotSpace != string::npos && lastNotSpace != string::npos) {
            LHS.push_back(token.substr(firstNotSpace, lastNotSpace - firstNotSpace + 1));
        } else {
            LHS.push_back("");
        }
    }

    return LHS;
}


//right hand side of fd
vector<string> rhs_parser(const string& fd) {
    vector<string> RHS;
    string temp = fd.substr(fd.find("->") + 2);

    istringstream stream(temp);
    string token;
    while (getline(stream, token, ',')) {
        //remove whitespace
        size_t firstNotSpace = token.find_first_not_of(" \t\n\v\f\r");
        size_t lastNotSpace = token.find_last_not_of(" \t\n\v\f\r");

        //push into vector
        if (firstNotSpace != string::npos && lastNotSpace != string::npos) {
            RHS.push_back(token.substr(firstNotSpace, lastNotSpace - firstNotSpace + 1));
        } else {
            RHS.push_back("");
        }
    }

    return RHS;
}

//checks if value in vector
template <typename T>
bool in_vector(const vector<T>& vec, const T& value) {
    return find(vec.begin(), vec.end(), value) != vec.end();
}

//finds position of item in vector
int find_position(const vector<string>& strings, const string& valueToFind) {
    auto it = find(strings.begin(), strings.end(), valueToFind);
    if (it != strings.end()) {
        //if found calculate index
        int index = distance(strings.begin(), it);
        return index;
    } else {
        //not found
        return -1;
    }
}

vector<Table> convertToBCNF(vector<Table> inputTables) {
  
    vector<Table> result;

    vector<string> LHS;

    for(auto& inputTable : inputTables){
        //store original FDs to check for changes
        vector<string> originalFDs = inputTable.fundamentalDep;

        //iterate through FD of the inputTable
        for(const auto& fd : originalFDs) {
            vector<string> temp = lhs_parser(fd);
            LHS.insert(result.end(), temp.begin(), temp.end());
            vector<string> RHS = rhs_parser(fd);
            bool isBCNF = true;

            //check if the FD violates BCNF
            for(const auto& rhsAttribute : RHS) {
                if(in_vector(LHS, rhsAttribute)) {
                    isBCNF = false;
                    break;
                }
            }

            if(!isBCNF) {
                //create a new table with FDs [LHS->RHS] and update inputTable by removing RHS attributes
                Table newTable = createTable(constructFD(temp, RHS), inputTable);
                inputTable.remove_columns(inputTable, RHS);
                result.push_back(newTable);
            }
        }

        //push updated table
        result.push_back(inputTable);
    }

    // print_vector(inputTable.fundamentalDep);
    // print_vector(LHS);
    // print_vector(RHS);
    return result;
}

#endif