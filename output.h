#ifndef OUTPUT_H
#define OUTPUT_H

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



//test code begin
void print_map(const unordered_map<string, vector<string>>& map) {
    //max width
    size_t maxWidth = 0;
    for (const auto& [attribute, values] : map) {
        maxWidth = max(maxWidth, attribute.length());
    }

    //columns
    for (const auto& [attribute, values] : map) {
        cout << setw(maxWidth) << left << attribute << ": ";
        for (const auto& value : values) {
            cout << setw(15) << value << " ";
        }
        cout << endl;
    }
}

void print_vector(const vector<string>& vec) {
    for (const string& element : vec) {
        cout << element << " ";
    }
    cout << endl;
}
//end of test code

//query output writing
void print_query(vector<Table> queries) {
    ofstream outputFile;
    outputFile.open("output.txt");

    if (outputFile.is_open()) {
      for(const auto& query : queries) {
        outputFile << "CREATE TABLE " << query.name << " (" << endl;
        for (size_t x = 0; x < query.attributes.size(); x++) {
            outputFile << "\t" << query.attributes[x] << " " << query.types[x];

            if (x < query.attributes.size() - 1) {
                outputFile << "," << endl;
            } else {
                outputFile << endl;
            }
        }
        outputFile << ");" << endl;
        outputFile << endl;
      }
      outputFile.close();

    } else {
        cout << "Error: Unable to open output file." << endl;
    }
}


#endif
