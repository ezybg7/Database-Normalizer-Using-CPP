#ifndef NF1_H
#define NF1_H

#include "header.h"
#include "output.h"

Table convertTo1NF(Table inputTable) {
    //Convert the map back to 1NF
    unordered_map<string, vector<string>> inputValues;

    //identify multivalued tuple
    //separate the different values
    //first value stays in original tuple
    //latter values created in new tuple
    //add new tuple to the end of the ordered map
    vector<vector<string>> newRows;
    for(int i = 0; i < inputTable.data[inputTable.attributes[0]].size(); i++)
    {
      bool copy = false;
      vector<string> row, row2;
      for(int j = 0; j < inputTable.attributes.size(); j++)
      {
        string current = inputTable.data[inputTable.attributes[j]][i];
        string secondPart = "";
        if(current.front() == '"' && current.back() == '"')
        {
          copy = true;
          secondPart = current.substr(current.find(',')+1, current.size()-current.find(',')-2);
          current = current.substr(1, current.find(',')-1);
          //this only checks for 2 values, need to be able to check for 2+ later
        }
        row.push_back(current);
        inputValues[inputTable.attributes[j]].push_back(current);
        if(secondPart != "")
          row2.push_back(secondPart);
        else
          row2.push_back(current);
        
      }
      //print_vector(row);
      if(copy)
        newRows.push_back(row2);
      //cout << endl;
    }
    //for each vector in newRows, add that to the data map
    for(const auto& row : newRows)
    {
      int index = 0;
      for(const string& element : row)
      {
        inputValues[inputTable.attributes[index]].push_back(element);
        index++;
      }
    }

    // for (const auto& [attribute, values] : inputTable.data) {
    //     for (const auto& value : values) {
    //         inputValues[attribute].push_back(value);
            
    //     }
    // }
    
    Table newTable(inputTable.attributes, inputTable.fundamentalDep, inputTable.keys, inputValues, inputTable.types);
    return newTable;
}

bool is1NF(Table inputTable)
{
  //missing "All entries in a column must be of the same kind" honestly idk how to do this
  //cuz there isn't a defined data type of regex for every attribute
  for (const auto& [attribute, values] : inputTable.data) {
        if(attribute.front() == '"' && attribute.back() == '"') //if nested relation exists
          return false;
        for (const auto& value : values) {
            //check for multivalued
            if(value.front() == '"' && value.back() == '"')
              return false;
        }
    }
  if(inputTable.keys.empty()) //if no defined primary key
    return false; //this is the last if statement temporarily, move up to top later
  return true;
}
#endif