#ifndef BCNF_H
#define BCNF_H

#include "header.h"

// Function to check if a set of attributes is a superkey
bool isSuperkey(const unordered_set<string>& attributes, const vector<pair<unordered_set<string>, unordered_set<string>>>& functionalDependencies) {
    unordered_set<string> closure = attributes;
    bool changed = true;

    // Compute closure of the attributes
    while (changed) {
        changed = false;
        for (const auto& fd : functionalDependencies) {
            if (includes(closure.begin(), closure.end(), fd.first.begin(), fd.first.end()) && !includes(closure.begin(), closure.end(), fd.second.begin(), fd.second.end())) {
                closure.insert(fd.second.begin(), fd.second.end());
                changed = true;
            }
        }
    }

    // If closure contains all attributes, it's a superkey
    return closure.size() == attributes.size();
}

// Function to convert a dataset into BCNF
vector<string> convertToBCNF(const vector<string>& dataset, const vector<pair<unordered_set<string>, unordered_set<string>>>& functionalDependencies) {
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

        // Add the row to the corresponding key in the resultMap
        resultMap[key].push_back(accumulate(fd.second.begin(), fd.second.end(), "", [&](string& s, const string& v) { return s.empty() ? values[v] : s + "," + values[v]; }));
    }

    // Construct result by combining rows with the same keys
    for (const auto& pair : resultMap) {
        // Check if the key is a superkey
        unordered_set<string> keyAttributes = unordered_set<string>(splitString(pair.first, ',').begin(), splitString(pair.first, ',').end());
        if (!isSuperkey(keyAttributes, functionalDependencies)) {
            // If not a superkey, decompose further
            for (const auto& row : pair.second) {
                vector<string> newRow;
                newRow.push_back(pair.first);
                newRow.push_back(row);
                result.push_back(accumulate(newRow.begin(), newRow.end(), "", [&](string& s, const string& v) { return s.empty() ? v : s + "," + v; }));
            }
        } else {
            // If it's a superkey, add the rows as they are
            for (const auto& row : pair.second) {
                result.push_back(pair.first + "," + row);
            }
        }
    }

    return result;
}

#endif