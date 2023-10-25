#include "nf1.h"
#include "output.h"

int Table::tableCount = 0;

int main(){
  const string file = "exampleInputTable.csv";
  const string fileFD = "functionalDependencies.txt";

  // vector<string> result = convertTo1NF(tupleMap);

  Table testTable = Table::parseCSV(file, fileFD);


  //print_vector(result);

  print_map(testTable.data);

  //print_map(convertTo1NF(tupleMap));



  return 0;
}
