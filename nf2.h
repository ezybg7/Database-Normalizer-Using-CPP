#ifndef NF2_H
#define NF2_H

#include "nf1.h"
#include "header.h"
#include "output.h"

//function to split by comma for the FDs
vector<string> parseFD(string input, vector<string> parsed)
{
  stringstream commaSplit(input);
  while(commaSplit.good())
  {
    string data;
    getline(commaSplit, data, ',');
    parsed.push_back(data);
  }
  return parsed;
}

bool IsSubset(vector<string> A, vector<string> B)
{
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    return includes(A.begin(), A.end(), B.begin(), B.end());
}

//template <class T> may have to make a template so attribute data types dont get messed up?
bool isFD(string a, string b, unordered_map<string, vector<string>> data)
{
  for(size_t i = 0; i < data[a].size(); i++)
  {
    string currentA = data[a][i];
    string currrentB = data[b][i];
    for(size_t j = 0; j < data[a].size(); j++)
    {
      if((i != j) && (currentA == data[a][j]))
      {
        if(currrentB != data[b][j])
        {
          //cout << currrentB << " does not equal " << data[b][j] << " for " << currentA << endl;
          return false;
        }
      }
    }
  }
  return true;
}

string constructFD(vector<string> LHS, vector<string> RHS)
{
  string output = "";
  for(const auto& left : LHS)
    output += left + ",";
  output = output.substr(0, output.size()-1);
  output += "->";
  for(const auto& right : RHS)
    output += right + ",";
  output = output.substr(0, output.size()-1);
  //cout << output << endl;
  return output;
}

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
        if(find(primaryKey.begin(), primaryKey.end(), attribute) == primaryKey.end())
        {
          nonKeyAttributes.push_back(attribute);
        }
    }
    vector<string> normalizedFDs;
    for(const auto& fd: inputTable.fundamentalDep)
    {
      string LHS = fd.substr(0, fd.find("->"));
      string RHS = fd.substr(fd.find("->")+2, fd.size()-1);
      vector<string> parsedLHS, parsedRHS;
      parsedLHS = parseFD(LHS, parsedLHS);
      parsedRHS = parseFD(RHS, parsedRHS);
      if((parsedLHS == primaryKey) || IsSubset(primaryKey, parsedLHS)) //if not a partial dependency or LHS is subset, keep it
      {
        normalizedFDs.push_back(fd);
        //cout << fd << endl;
      }
      //if none of LHS is in the primary key, then make the primary keys the LHS
      else 
      {
        vector<string> newLHS, newRHS;
        for(const auto& LHS : parsedLHS)
        {
          //if one of the elements in parsedLHS is in primary key
          if(find(primaryKey.begin(), primaryKey.end(), LHS) != primaryKey.end()) 
          {
            //cout << "LHS: " << LHS << " found in primary key: ";
            //print_vector(primaryKey);
            newLHS.push_back(LHS);
          }
          for(const auto& RHS : parsedRHS)
          {
            //check if LHS elements are actually FD to RHS elements
            if(isFD(LHS, RHS, inputTable.data))
            {
              newRHS.push_back(RHS);
              //cout << "pushing back " << RHS << endl;
            }
          }
        }
        if(newLHS.size() == 0) //if no match on LHS, all primary keys are on LHS automatically
        {
          newLHS = primaryKey;
          newRHS.clear();
          for(const auto& attribute : inputTable.attributes)
          {
            if(!(find(primaryKey.begin(), primaryKey.end(), attribute) != primaryKey.end()))
            { //add all attributes that are FD to the composite key
              bool addToFD = true;
              for(const auto& pKey : primaryKey)
              {
                if(isFD(pKey, attribute, inputTable.data))
                  addToFD = false;
              }
              if(addToFD)
                newRHS.push_back(attribute);
            }
          }
        }
        normalizedFDs.push_back(constructFD(newLHS, newRHS));
      }
    }
    cout << "NORMALIZED FDS: " << endl;
    for (const string& element : normalizedFDs) 
        cout << element << " " << endl;
    for(const auto& fd : inputTable.fundamentalDep)
    {
      string LHS = fd.substr(0, fd.find("->"));
      string RHS = fd.substr(fd.find("->")+2, fd.size()-1);
      //cases (in priority):
      //1: fd equals the entirely of the primaryKey vector (not partial)
      //2: fd equals one/some of the primaryKey vector
      //3: 
      //cout << fd.substr(0, fd.find("->")) << endl;
      //case 2:
      for(const auto& key : primaryKey)
      {
        //if(fd == primaryKey)
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
            newDTs.push_back(determineDataType(data));
          }}
          {stringstream commaSplit(RHS);
          while(commaSplit.good())
          {
            string data;
            getline(commaSplit, data, ',');
            newAttributes.push_back(data);
            newDTs.push_back(determineDataType(data));
          }}
          print_vector(newDTs);

          unordered_map<string, vector<string>> newData;
          for(const auto& [attribute, values] : inputTable.data)
          {
            for(const auto& newAt : newAttributes)
            {
              if(attribute == newAt)
              {
                for(const auto& value : values)
                {
                  newData[attribute].push_back(value);
                }  
              }
            }
          }
          //print_map(newData);
          Table newTable(newAttributes, newFDs, newKeys, newData, newDTs);
          result.push_back(newTable);
        }
        else //new table will include composite key and remaining attributes
        {
          unordered_map<string, vector<string>> newData;
          vector<string> newAttributes; 
          vector<string> newDTs; 
          vector<string> newFDs;
          vector<string> newKeys = primaryKey; //temp
          for(const auto& key : primaryKey)
            newAttributes.push_back(key);
          // {stringstream commaSplit(LHS);
          // while(commaSplit.good())
          // {
          //   string data;
          //   getline(commaSplit, data, ',');
          //   cout << "hi" << data << endl;
          //   newAttributes.push_back(data);
          //   newDTs.push_back(determineDataType(LHS));
          // }}  

          for(const auto& [attribute, values] : inputTable.data)
          {
            for(const auto& newAT : newAttributes)
            {
              if(attribute == key)
              {
                for(const auto& value : values)
                {
                  newData[attribute].push_back(value);
                }  
              }
            }
          }
          cout << "3rd case data: " << endl;
          print_map(newData);
          // Table newTable(newAttributes, newFDs, newKeys, newData, newDTs);
          // result.push_back(newTable);
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