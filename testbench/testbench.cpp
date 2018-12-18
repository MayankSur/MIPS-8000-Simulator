#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

struct resultFormat {
    string TestID;
    string Instruction;
    string Status;
    string Author;
    string Message;
}

resultFormat(string command, uint16_t expectedOutput, uint16_t testInput) {

    if (expectedOutput < (system(command)) {
        resultFomart.Status ==\ "Pass"
    } // Comparison to answerfile

    return
}

int main (int argc, char* argv[]) {

  if ( argc != 2) {
	  cerr << "Incorrect no. parameters entered" << endl;
	  return -1;
  } // Check if commandline input is structured correctly

  char command[255];

  // Following commands formulate a string that delcares the path to the simulator: required by the system() function for comparison with testcases
  command = argv[1]; // command line input of path e.g. bin/simulator
  strcat(command, " testfile.bin"); // testcases

  ret_val(system(command));
  if(0 != ret_val) {
      cerr << "There was an error" << endl;
      return -1;
  } // Check path exists

  // Declaring all required files
  ifstream testcases.bin // testcases
  ifstream expectedresults.bin
  ofstream results.csv // resultsfile
  ofstream logfile.txt // temp results from function

  // Input file
  uint_16 test;

  while(uint_16.get(test)){
      ROM[i]=a;

    string(string command, uint16_t answerfile.bin[i], uint16_t testfile.bin[i]);

  //open file stream for inputfile.bin (yep!)
  //write ur binary code into the file (yep!)
  //close file stream (yep!)

    //write your result into the csv file (yep!) make it into a function that takes and 'expect' and 'actual'
  //close it
  }

  // Closing all files
  testcases.bin.close();
  expectedresults.bin.close();
  results.csv.close();
  log.txt.close();

return 0;

}
