#ifndef NF1_H
#define NF1_H

#include "header.h"
#include "output.h"

vector<string> convertTo1NF(Table resultMap) {
    //Convert the map back to 1NF
    vector<string> result;
    for (const auto& pair : resultMap.data) {
        stringstream rowStream;
        for (const auto& value : pair.second) {
            rowStream << value << ",";
            cout << value << ",";
        }
        cout << endl;
        string row = rowStream.str();
        //Remove the trailing comma
        row.pop_back();
        result.push_back(row);
    }

    return result;
}
#endif