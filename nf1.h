#ifndef NF1_H
#define NF1_H

#include <iostream>

using namespace std;

vector<string> convertTo1NF(const vector<string>& dataset) {
    unordered_map<string, vector<string>> resultMap;

    //Iterate through the dataset and organize data based on keys
    for (const auto& row : dataset) {
        vector<string> values = splitString(row, ',');

        //Use the first column as the key (superkey) for organizing data
        string key = values[0];
        if (resultMap.find(key) == resultMap.end()) {
            resultMap[key] = values;
        } else {
            //Merge rows with the same key by concatenating values
            for (size_t i = 1; i < values.size(); ++i) {
                resultMap[key].push_back(values[i]);
            }
        }
    }

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