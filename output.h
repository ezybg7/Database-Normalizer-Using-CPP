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
            cout << value << " ";
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

void print_query(Table query) {
    ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << "CREATE TABLE " << query.name << " (" << endl;
    for(string i : query.attributes){
        outputFile << "\t" << i << endl;
    }

    
    outputFile.close();
}


#endif
