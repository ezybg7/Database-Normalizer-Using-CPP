#include "nf1.h"
//#include "nf2.h"
//#include "nf3.h"
//#include "bcnf.h"
//#include "nf4.h"
//#include "nf5.h"
#include "output.h"

int Table::tableCount = 0;

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



  // int numTuples = getTupleAmount(file);
  // vector<string> attributes = getAttributes(file);
  // vector<vector<string>> tuples = returnTuples(file);
  // vector<string> keys; //fixme : add keys input


  // unordered_map<string, vector<string>> tupleMap = mapReturn(tuples, attributes);

  // vector<string> result = convertTo1NF(tupleMap);

  Table testTable = Table::parseCSV(file);

  //print_vector(result);

  print_map(testTable.data);

  //print_map(convertTo1NF(tupleMap));



  return 0;
}
