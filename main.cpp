#include "nf1.h"
//#include "nf2.h"

int main(){
  const string file = "exampleInputTable.csv";
  const string fileFD = "functionalDependencies.txt";

  //opening file
  ifstream input;
  string line;
  input.open(fileFD);

  //getting functional dependencies
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

  print_map(tupleMap);

  return 0;
}
