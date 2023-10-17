#include "nf5.h" 
#include "header.h"

int main(){
  const string file = "exampleInputTable.csv";
  const string fileFD = "functionalDependencies.txt";

  ifstream input;
  string line;
  input.open(fileFD);

  vector<string> funcDeps;
  if (input.is_open())
  {
    while( getline(input,line) )
    {
      funcDeps.push_back(line);
    }
    input.close();
  }

  int numTuples = getTupleAmount(file);
  vector<string> attributes = getAttributes(file);
  vector<vector<string>> tuples = returnTuples(file);
  vector<string> keys;
  unordered_map<string, vector<string>> tupleMap = mapReturn(tuples, attributes);
  
  return 0;
}
