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
    for(size_t i = 0; i < inputTable.data[inputTable.attributes[0]].size(); i++)
    {
      bool copy = false;
      vector<string> multiValues;
      vector<string> currentRow;
      int dupIndex;
      for(size_t j = 0; j < inputTable.attributes.size(); j++)
      {
        string current = inputTable.data[inputTable.attributes[j]][i];
        currentRow.push_back(current);
      }
      for(size_t j = 0; j < inputTable.attributes.size(); j++)
      {
        string current = inputTable.data[inputTable.attributes[j]][i];
        if(current.front() == '"' && current.back() == '"')
        {
          copy = true;
          dupIndex = j;
          stringstream commaSplit(current.substr(1, current.size()-2));
          while(commaSplit.good())
          {
            string data;
            getline(commaSplit, data, ',');
            multiValues.push_back(data);
          }
          // for(size_t z = 0; z < multiValues.size(); z++)
          //   cout << multiValues[z] << endl;
          current = current.substr(1, current.find(',')-1);
        }
        inputValues[inputTable.attributes[j]].push_back(current);
      }
      if(copy)
      {
        for(size_t j = 1; j < multiValues.size(); j++)
        {
          vector<string> row = currentRow;
          row[dupIndex] = multiValues[j];
          newRows.push_back(row);
        }
      }
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