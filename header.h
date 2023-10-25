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

      while (getline(ss, attribute, ',')) {
          attributes.push_back(attribute);
      }
      

      Table table(attributes, FDinput, {});

      while (getline(file, line)) {

        stringstream ss(line);
        string value;
        vector<string> dataRow;
        int index = 0;

        while (getline(ss, value, ',')) {
            if (index >= attributes.size()) {
                cerr << "Error: Number of columns in a row exceeds the number of attributes." << endl;
                return table;
            }

            //parses for multivalued
            if (value.front() == '"' && value.back() == '"')
                value = value.substr(1, value.size() - 2);

            stringstream valueStream(value);
            string singleValue;

            while (getline(valueStream, singleValue, '\"'))
                table.data[attributes[index]].push_back(singleValue);
            index++;
        }
        file.close();
        
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