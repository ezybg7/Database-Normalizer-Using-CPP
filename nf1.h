#ifndef NF1_H
#define NF1_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> convertTo1NF(const unordered_map<string, vector<string>> resultMap) {
    //Convert the map back to 1NF
    vector<string> result;
    for (const auto& pair : resultMap) {
        stringstream rowStream;
        for (const auto& value : pair.second) {
            rowStream << value << ",";
        }
        string row = rowStream.str();
        //Remove the trailing comma
        row.pop_back();
        result.push_back(row);
    }

    return result;
}
#endif