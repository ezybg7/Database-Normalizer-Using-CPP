#include "nf1.h"
#include "nf2.h"
#include "nf3.h"
#include "output.h"

int Table::tableCount = 0;

int main(){
  const string file = "exampleInputTable.csv";
  const string fileFD = "functionalDependencies.txt";

  Table testTable = Table::parseCSV(file, fileFD);

  char form, find;

  cout << "Choice of the highest normal form to reach (1: 1NF, 2: 2NF, 3: 3NF, B: BCNF, 4: 4NF, 5: 5NF):" << endl;
  cin >> form;
  cout << "Find the highest normal form of the input table? (1: Yes, 2: No):" << endl;
  cin >> find;

  vector<Table> results;

  switch(form) {
    case '1':
      results.push_back(convertTo1NF(testTable));
      break;
    case '2':
      results = convertTo2NF(testTable);
      break;
    case '3':
      results = convertTo3NF(testTable);
      break;
    case 'B':
      //results = convertToBCNF(testTable);
      break;
    case '4':
      //results = convertTo4NF(testTable);
      break;
    case '5':
      //results = convertTo5NF(testTable);
      break;
    default:
      cout << "Not a valid input" << endl;
      break;
  }

  //FIXME: add new function that tests all tests, 
  //If NF1, test for NF2, so on, so tests can be easier, i.e. only testing for FDs etc.
  //If NF5, return NF5
  //Each function should return, if not NF2, return NF1, if not NF3, return NF2, etc. 
  switch(find) {
    //Yes
    case '1':
      break;
    //No
    case '2':
      break;
  }
  for(size_t i = 0; i < results.size(); i++)
  {
    print_vector(results[i].attributes);
    print_vector(results[i].types);
    print_map(results[i].data);
  }
  print_query(results);
  

  return 0;
}
