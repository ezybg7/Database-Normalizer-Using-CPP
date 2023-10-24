#ifndef NF3_H
#define NF3_H

#include "header.h"
#include "output.h"

vector<string> convertTo3NF(const vector<string>& dataset, const vector<pair<unordered_set<string>, unordered_set<string>>>& functionalDependencies) {
    vector<string> result;

    // Create a map for storing table rows based on the key
    unordered_map<string, vector<string>> resultMap;

    // Iterate through the dataset and organize data based on keys
    for (const auto& row : dataset) {
        vector<string> values = splitString(row, ',');

        // Extract key attributes based on functional dependencies
        string key;
        for (const auto& fd : functionalDependencies) {
            if (includes(fd.first.begin(), fd.first.end(), values.begin(), values.end())) {
                key = accumulate(fd.first.begin(), fd.first.end(), key, [](string& k, const string& v) { return k.empty() ? v : k + "," + v; });
                break;
            }
        }

        resultMap[key].push_back(accumulate(fd.second.begin(), fd.second.end(), "", [&](string& s, const string& v) { return s.empty() ? values[v] : s + "," + values[v]; }));
    }

    // Construct result by combining rows with the same keys
    for (const auto& pair : resultMap) {
        for (const auto& row : pair.second) {
            result.push_back(pair.first + "," + row);
        }
    }

    return result;
}

#endif