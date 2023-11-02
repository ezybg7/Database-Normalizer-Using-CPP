#ifndef NF2_H
#define NF2_H

#include "nf1.h"
#include "header.h"
#include "output.h"

//function to split by comma here im too lazy to do it rn

//Check if it is in 1NF before operating
vector<Table> convertTo2NF(Table inputTable)
{
    if(!is1NF(inputTable))
        inputTable = convertTo1NF(inputTable);
    
    vector<Table> result;
    //Extract primary key and non-key attributes
    vector<string> primaryKey = inputTable.keys;
    vector<string> nonKeyAttributes;
    for (const auto &attribute : inputTable.attributes)
    {
        if (find(primaryKey.begin(), primaryKey.end(), attribute) == primaryKey.end())
        {
            nonKeyAttributes.push_back(attribute);
        }
    }
    //print_vector(inputTable.fundamentalDep);
    for(const auto& fd : inputTable.fundamentalDep)
    {
      //also need to parse the FD to get the LHS and RHS
      string LHS = fd.substr(0, fd.find("->"));
      string RHS = fd.substr(fd.find("->")+2, fd.size()-1);
      //cases (in priority):
      //1: fd equals the entirely of the primaryKey vector
      //2: fd equals one/some of the primaryKey vector
      //cout << fd.substr(0, fd.find("->")) << endl;
      //case 2:
      for(const auto& key : primaryKey)
      {
        if(LHS == key)
        {
          vector<string> newDTs; 
          vector<string> newFDs;
          newFDs.push_back(fd);

          vector<string> newKeys;
          newKeys.push_back(LHS);

          vector<string> newAttributes; 
          {stringstream commaSplit(LHS);
          while(commaSplit.good())
          {
            string data;
            getline(commaSplit, data, ',');
            newAttributes.push_back(data);
            newDTs.push_back(determineDataType(LHS));
          }}
          {stringstream commaSplit(RHS);
          while(commaSplit.good())
          {
            string data;
            getline(commaSplit, data, ',');
            newAttributes.push_back(data);
            newDTs.push_back(determineDataType(RHS));
          }}
          print_vector(newDTs);

          Table newTable(newAttributes, newFDs, newKeys, {}, newDTs);
        }
      }
      
    }
    // cout << "keys:" << endl;
    // print_vector(primaryKey);
    // cout << "nonkeys:" << endl;
    // print_vector(nonKeyAttributes);




    return result;
}
#endif