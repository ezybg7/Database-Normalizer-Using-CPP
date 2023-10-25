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
#include <numeric>
#include <algorithm>

using namespace std;
//table struct so we can store each table
struct Table {
    string name;
    vector<string> attributes, keys, fundamentalDep;
    unordered_map<string, vector<string>> data;

    static int tableCount;

    //constructor that increments table
    Table(const vector<string>& tableAttributes, const vector<string> fd, const vector<string>& tableKeys)
        : name("Table" + to_string(++tableCount)), attributes(tableAttributes), fundamentalDep(fd), keys(tableKeys)  {}

    //parser
    static Table parseCSV(const string& filename, const string& fileFD) {
      
      ifstream parseFD(fileFD);
      string line2;
      vector<string> FDinput;
      if (parseFD.is_open())
      {
        while( getline(parseFD,line2) )
          FDinput.push_back(line2);
        parseFD.close();
      }
      
      ifstream file(filename);
      string line;

      getline(file, line);
      stringstream ss(line);
      string attribute;
      vector<string> attributes;

      //gets attributes
      while (getline(ss, attribute, ',')) {
        attributes.push_back(attribute);
      }
      //creates a table with attributes
      Table table(attributes, FDinput, {}); 

      //actual parsing of data
      while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> dataRow;
        bool inQuotes = false;
        string tempValue = "";

        while (getline(ss, value, ',')) {
          if (!inQuotes) {
            //multivalued
            if (value.front() == '\"' && value.back() == '\"') 
              dataRow.push_back(value.substr(1, value.size() - 2));
            else if (value.front() == '\"') {
              //multi start
              inQuotes = true;
              tempValue = value;
            } 
            else
              dataRow.push_back(value);
          } 
          else {
            //concatinating values
            tempValue += "," + value;
            if (value.back() == '\"') {
              //multi end
              inQuotes = false;
              dataRow.push_back(tempValue);
            }
          }
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

// //creates unordered map using attributes and tuples, essentially creating each collumn. 
// unordered_map<string, vector<string>> mapReturn(vector<vector<string>> tuples, vector<string> attributes)
// {
//   unordered_map<string, vector<string>> resultMap;

//   for(int i = 0; i < attributes.size(); i++)
//   {
//     string key = attributes[i];
//     for(int j = 0; j < tuples.size(); j++)
//     {
//       resultMap[key].push_back(tuples[j][i]);
//       //cout << resultMap[key].back() << endl;
//     }
//   }
//   return resultMap;
// }

#endif