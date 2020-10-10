#include <iostream>
#include <fstream>
#include "generatePre.cpp"
#include "generateObj.cpp"
using namespace std;

int main (int argc, char **argv) {
    string command, filename;

    command = argv[1];
    filename = argv[2];

    if(command == "-p")
        generatePre(filename);
    else if(command == "-o")
        generateObj(filename);
    
  return 0;
}