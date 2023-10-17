#ifndef HEADER_H
#define HEADER_H

#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

vector<string> getAttributes(string file)
{
  string line = "", temp;
  vector<string> attributeList;

  ifstream fin; 
  fin.open(file.c_str());
  getline(fin, line);
  stringstream attributes(line);

  while(getline(attributes, temp, ','))
    attributeList.push_back(temp);
  fin.close();
  return attributeList;
}

int getTupleAmount(string file)
{
  string line = "", temp;
  int count = 0;

  ifstream fin; 
  fin.open(file.c_str());
  while(getline(fin, line))
    count++;
  fin.close();
  return --count;
}

vector<vector<string>> returnTuples(string file)
{
  string line = "";
  
  ifstream fin{file};
  vector<vector<string>> tuples;

  getline(fin, line);
  for(string line; getline(fin, line);) 
  {
    stringstream input(move(line));
    vector<string> row;
    if(!tuples.empty()) 
      row.reserve(tuples.front().size());
    for(string value; getline(input, value, ',');) 
      row.push_back(move(value));
    tuples.push_back(move(row));
  }
  
  for(const vector<string>& row : tuples) 
  {
    for(const string& value : row)
      cout << setw(15) << value;
    cout << "\n";
  }
  fin.close();
  return tuples;
}

#endif