#include "nf1.h"
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
  //fixme : add functional dependences to the table after it has been made
  vector<string> funcDeps;
  if (input.is_open())
  {
    while( getline(input,line) )
    {
      funcDeps.push_back(line);
    }
    input.close();
  }

  // vector<string> result = convertTo1NF(tupleMap);

  Table testTable = Table::parseCSV(file, fileFD);


  //print_vector(result);

  print_map(testTable.data);

  //print_map(convertTo1NF(tupleMap));



  return 0;
}
