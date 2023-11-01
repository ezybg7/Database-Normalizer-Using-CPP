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
#include <cctype>

using namespace std;

//determine data types
string determineDataType(const string& input) {
  if (input.empty()) {
    return "EMPTY";
  }

  //check int
  bool isInteger = true;
  for (char c : input) {
    if (!isdigit(c)) {
      isInteger = false;
      break;
    }
  }

  //output
  if (isInteger) {
    return "INT";
  } else {
    //check date
    istringstream dateSS(input);
    int month, day, year;
    char delimiter;

    //takes in whole input of date format month_int/date_int/year
    dateSS >> month >> delimiter >> day >> delimiter >> year;

    if (delimiter == '/') {
      return "DATE";
    } else {
      return "VARCHAR(255)";
    }
  }
}

//table struct so we can store each table
struct Table {
  string name;
  vector<string> attributes, types, keys, fundamentalDep;
  unordered_map<string, vector<string>> data;

  static int tableCount;

  //constructor
  Table(const vector<string>& tableAttributes, const vector<string> fd, const vector<string>& tableKeys, unordered_map<string, vector<string>> tableData, const vector<string> type)
      : name("Table" + to_string(++tableCount)), attributes(tableAttributes), fundamentalDep(fd), keys(tableKeys), data(tableData), types(type)  {}

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

    //getting types
    ifstream typeFile(filename);

    string csvLine, field;

    //ignores first line so we need 2 getlines
    getline(typeFile, csvLine);
    getline(typeFile, csvLine);
    
    istringstream ss2(csvLine);
    vector<string> dataTypes;

    while (getline(ss2, field, ',')) {
      string dataType = determineDataType(field);
      dataTypes.push_back(dataType);
    }
    typeFile.close();
    
    //creates a table with attributes
    Table table(attributes, FDinput, {}, {}, dataTypes); //fixme dataTypes isn't being set correctly in

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
        } else {
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
    file.close();
    
    return table;
  }
};

#endif