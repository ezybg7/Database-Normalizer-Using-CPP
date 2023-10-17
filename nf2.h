#ifndef NF2_H
#define NF2_H

#include "nf1.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

vector<string> convertTo2NF(const vector<string>& dataset) {
    //Convert the dataset to 1NF first
    vector<string> datasetIn1NF = convertTo1NF(dataset);

    unordered_map<string, vector<string>> resultMap;

    //Iterate through the 1NF dataset and organize data based on keys
    for (const auto& row : datasetIn1NF) {
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

    //Convert the map back to vector for 2NF representation
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