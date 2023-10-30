#include "nf1.h"
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

  Table result({}, {}, {}, {}, {}); 

  switch(form) {
    case '1':
      result = convertTo1NF(testTable);
      break;
    case '2':
      //result = convertTo2NF(testTable);
      break;
    case '3':
      //result = convertTo3NF(testTable);
      break;
    case 'B':
      //result = convertToBCNF(testTable);
      break;
    case '4':
      //result = convertTo4NF(testTable);
      break;
    case '5':
      //result = convertTo5NF(testTable);
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
  print_vector(result.attributes);
  print_vector(result.types);
  print_map(result.data);
  print_query(result);

  return 0;
}
