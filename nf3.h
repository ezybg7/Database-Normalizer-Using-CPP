#ifndef NF3_H
#define NF3_H

#include "header.h"
#include "output.h"
#include "nf1.h"
#include "nf2.h"

vector<Table> convertTo3NF(Table inputTable)
{
  vector<Table> convertedInput;
  if(!is2NF(inputTable))
  {
    convertedInput = convertTo2NF(inputTable);
  }
  

  

  /*general rundown?
  -for each table, look at its FDs
  -check if any of the FDs have a non-prime attribute on LHS
  -if a non-prime attribute is on the LHS, check if it is on the RHS for another FD
  */
  for(const auto& tableElement : convertedInput)
  {
    for(const auto& fd : tableElement.fundamentalDep)
    {
      string LHS = fd.substr(0, fd.find("->"));
      string RHS = fd.substr(fd.find("->")+2, fd.size()-1);
      vector<string> parsedLHS, parsedRHS;
      parsedLHS = parseFD(LHS, parsedLHS);
      parsedRHS = parseFD(RHS, parsedRHS);
      for(const auto& LHS : parsedLHS)
      {
        if(!(find(tableElement.keys.begin(), tableElement.keys.end(), LHS) != tableElement.keys.end()))
        {//if attribute on LHS is not a primary key
          //search for all other FDs to see if the LHS is on the RHS of another FD with a primary key LHS
        }
      }
    }
  }

    // Table tableIn2NF = convertTo2NF(inputTable);

    // // Extract primary key and non-key attributes
    // vector<string> primaryKey = tableIn2NF.keys;
    // vector<string> nonKeyAttributes;
    // for (const auto &attribute : tableIn2NF.attributes)
    // {
    //     if (find(primaryKey.begin(), primaryKey.end(), attribute) == primaryKey.end())
    //     {
    //         nonKeyAttributes.push_back(attribute);
    //     }
    // }
    // vector<Table> result;

    // return result;
    return convertedInput;
}

#endif