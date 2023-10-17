#include "nf5.h" 
#include "header.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

int main(){
  const string file = "exampleInputTable.csv";

  vector<string> row;
  int numTuples = getTupleAmount(file);
  vector<string> attributes = getAttributes(file);
  vector<vector<string>> tuples = returnTuples(file);
  
  return 0;
}
