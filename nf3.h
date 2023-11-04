#ifndef NF3_H
#define NF3_H

#include "header.h"
#include "output.h"
#include "nf1.h"
#include "nf2.h"

vector<Table> convertTo3NF(Table inputTable)
{
  vector<Table> convertedTables;
  if(!is2NF(inputTable))
    convertedTables = convertTo2NF(inputTable);
  else
    convertedTables.push_back(inputTable);
  /*general rundown?
  -for each table, look at its FDs
  -check if any of the FDs have a non-prime attribute on LHS
  -if a non-prime attribute is on the LHS, check if it is on the RHS for another FD
  */
  vector<string> transitiveFDs;
  for(const auto& tableElement : convertedTables)
  {
    for(const auto& fd : tableElement.fundamentalDep)
    {
      string LHS = fd.substr(0, fd.find("->"));
      string RHS = fd.substr(fd.find("->")+2, fd.size()-1);
      vector<string> parsedLHS, parsedRHS;
      parsedLHS = parseFD(LHS, parsedLHS);
      parsedRHS = parseFD(RHS, parsedRHS);
      for(const auto& RHS : parsedRHS)
      {
        if(!(find(tableElement.keys.begin(), tableElement.keys.end(), RHS) != tableElement.keys.end()))
        {//take all RHS attributes and see if any of them are FD of each other (therefore transitive?)
          for(const auto& element : parsedRHS)
          {
            if(RHS != element) 
            {//need to also check if the LHS is actually FD to every RHS
              for(const auto& LHS : parsedLHS)
              {
                if(!isFD(LHS, RHS, tableElement.data))
                {
                  if(isFD(RHS, element, tableElement.data)) 
                  {
                    //cout << fd << endl;
                    vector<string> newParsedRHS;
                    for(const auto& rhsElement : parsedRHS)
                    {
                      if(rhsElement != element)
                        newParsedRHS.push_back(rhsElement);
                    }
                    string modifiedFD = constructFD(parsedLHS, newParsedRHS);
                    string newTransFD = constructFD(RHS, element);
                    string preventTransFDDup = constructFD(element, RHS);
                    bool reverseExists = find(transitiveFDs.begin(), transitiveFDs.end(), preventTransFDDup) != transitiveFDs.end();
                    bool alreadyExists = find(transitiveFDs.begin(), transitiveFDs.end(), newTransFD) != transitiveFDs.end();
                    if((!reverseExists) && (!alreadyExists))
                    {
                      transitiveFDs.push_back(modifiedFD);
                      transitiveFDs.push_back(newTransFD);
                    }
                  }
                }
                else
                {
                  bool alreadyExists = find(transitiveFDs.begin(), transitiveFDs.end(), fd) != transitiveFDs.end();
                  if(!alreadyExists)
                    transitiveFDs.push_back(fd);
                }
              }
            }
          }
        }
      }
    }
  }//wow... please ignore that monstrosity above
  //print_vector(transitiveFDs);
  vector<Table> result;
  for(const auto& fd : transitiveFDs)
  {
    Table newTable = createTable(fd, inputTable);
    result.push_back(newTable);
  }
  return result;
}

bool is3NF(Table inputTable)
{
  if(!is2NF(inputTable))
    return false;
  for(const auto& fd : inputTable.fundamentalDep)
  {
    string LHS = fd.substr(0, fd.find("->"));
    string RHS = fd.substr(fd.find("->")+2, fd.size()-1);
    vector<string> parsedLHS, parsedRHS;
    parsedLHS = parseFD(LHS, parsedLHS);
    parsedRHS = parseFD(RHS, parsedRHS);
    for(const auto& LHS : parsedLHS)
    {
      for(const auto& RHS : parsedRHS)
      { //probably just a simple check to see if all LHS is FD to RHS
        if(!(isFD(LHS, RHS, inputTable.data)))
          return false;  
      }
    }
  }
  return true;
}

#endif