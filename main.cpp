#include "nf5.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

vector<string> getAttributes(string file);

int getTupleAmount(string file);

vector<vector<string>> returnTuples(string file);

int main(){
  const string file = "exampleInputTable.csv";

  vector<string> row;
  int numTuples = getTupleAmount(file);
  vector<string> attributes = getAttributes(file);
  vector<vector<string>> tuples = returnTuples(file);
  
  return 0;
}

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
  /*
  for(const vector<string>& row : tuples) 
  {
    for(const string& value : row)
      cout << setw(15) << value;
    cout << "\n";
  }*/
  fin.close();
  return tuples;
}