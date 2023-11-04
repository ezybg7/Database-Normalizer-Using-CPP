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
bool in_vector(const vector<string>& vec, const string& value) {
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
    vector<vector<string>> LHS, RHS;

    for(auto& inputTable : inputTables){
        //lhs & rhs[[0,1,2,3],[0,1,2,3]]
        //access by using i.e. lhs[i][j]
        for(const auto& fd : inputTable.fundamentalDep)
        {
            cout << fd << endl;
            LHS.push_back(lhs_parser(fd));
            RHS.push_back(rhs_parser(fd));
            cout << "lhs size: " << LHS.size() << endl;
            cout << "rhs size: " << RHS.size() << endl;
            //checks all functional dependencies of table
            for(size_t i = 0; i < LHS.size(); i++){
                //checks all the RHS values and see if they exist within LHS
                for(size_t j = 0; j < RHS[i].size(); j++){
                    cout << "comparing " << i << " : " << j << endl;
                    //if it exists make a table based on it and push the table into result
                    if(in_vector(LHS[i], RHS[i][j])){
                        vector<string> rmAt;

                        cout << "HIIIIIIIIIIIIIIIIIII" << endl;
                        Table newTable = createTable(constructFD(LHS[i], RHS[i]), inputTable);
                        result.push_back(newTable);
                        //find which fd has rhs in lhs
                        int fdPos = find_position(LHS[i],RHS[i][j]);
                        //remove that attribute that is dupe
                        rmAt.push_back(RHS[fdPos][0]);
                        
                        //pushing inputTable that has had attribute removed
                        inputTable.remove_columns(inputTable, rmAt);

                        break;
                    }
                }
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