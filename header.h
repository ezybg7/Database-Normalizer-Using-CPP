#ifndef HEADER_H
#define HEADER_H

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
//table struct so we can store each table
struct Table {
    string name;
    vector<string> attributes;
    vector<string> keys;
    vector<string> fd;
    unordered_map<string, vector<string>> data;

    static int tableCount;

    //constructor that increments table
    Table(const vector<string>& tableAttributes, const vector<string>& tableKeys, const vector<string>& fucntionalDependencies)
        : name("Table" + to_string(++tableCount)), attributes(tableAttributes), keys(tableKeys), fd(fucntionalDependencies) {}

    //parser
      {
        while( getline(parseFD,line2) )
          FDinput.push_back(line2);
        parseFD.close();
      }
    vector<string> attributes;

    while (getline(ss, attribute, ',')) {
      attributes.push_back(attribute);
    }

    Table table(attributes);

    //reads rest of the data
    while (getline(file, line)) {
      stringstream ss(line);
      string value;
      vector<string> dataRow;

      while (getline(ss, value, ',')) {
        //detects multivalue
        if (value.front() == '\"' && value.back() == '\"')
          dataRow.push_back(value.substr(1, value.size() - 2));
        else
          dataRow.push_back(value);
      }

      if (dataRow.size() != attributes.size()) {
        cerr << "Error: Number of columns in a row does not match the number of attributes." << endl;
        return table;
      }

      //store data into table
      for (size_t i = 0; i < attributes.size(); ++i) {
        table.data[attributes[i]].push_back(dataRow[i]);
      }
    }

    return table;
  }
};

#endif