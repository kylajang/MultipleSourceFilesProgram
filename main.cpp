#define _USE_MATH_DEFINES
#include <cmath>
#include "professor_lib.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::endl, std::cin;
using std::string;
using std::ofstream;
using std::ifstream;

// Making the first function
double calculateSmoid(double x){
  // Declaring my variables
  double y;

  // Writing the formula to the program
  y =  (pow (M_E, x)) / (pow (M_E, x) + 1);

  return y;
}

// Making the second function
bool convertFileToSmoid(string source_file_name,
  string dest_file_name, string& message, int& record_count){
  // Declaring my variables
  string ok("OK");
  message = ok;

  // opening source_file_name for reading
  ifstream ifs(source_file_name);
  // error checking - making sure file opens
  if (ifs.bad()){
    message = "Unable to open input file";
    // returning failure if file won't open
    return false;
  }

  ofstream ofs(dest_file_name);
    // error checking the output file
    if (ofs.bad()){
      message = "Unable to open output file";
      // returning failure if file won't open
      return false;
    }

    for(string line; std::getline(ifs, line);) {
      double y, x = std::stof(line);
      y = calculateSmoid(x);
      // printing out the result
      ofs << x << " " << y << endl;
      record_count++;
    }

    // closing the file
    ofs.close();
    ifs.close();
    return true;
}

// The main function
int main(int argc, char const *argv[]) {
  // Declaring my variables
  bool valid;
  string message;
  int record_count = 0;

  // Checking for correct # of command line arguments
  if(argc != 3){
    cout << "Invalid command line arguments!" << endl;
    cout << argc << endl;
    // Exiting with an error code 1
    exit(2);
  }
  // Printing the file conversion message
  cout << "Begin file conversion of input file " << argv[1] << " to output file "
  << argv[2] << " using calculateSmoid." << endl;

  valid = convertFileToSmoid("in.txt", "out.txt", message, record_count);
  
  // checking if the valid variable is true of false
  if(valid == true){
    cout << "File conversion was successful; Converted " << record_count
    << "; " << message << endl;
  }

  else{
    cout << "Failed to convert that file; Message was: " << message << endl;
    // Exiting with an error code 1
    exit(1);
  }
  // After running the program successfully
  renderAndPrintConvertedFile(argv[2]);

  return 0;
}
