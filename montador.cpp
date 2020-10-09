#include <iostream>
#include <fstream>
#include "generatePre.cpp"
using namespace std;

int main (int argc, char **argv) {
    string command, filename;
    // string line = "MULT X1, X2", sub_arg, aux;
    // size_t pos = 0;

    // sub_arg = line.substr(line.find_first_of(" ")+1, line.length()-(line.find_first_of(" ")+1));
    // cout << sub_arg << endl;
    // sub_arg.erase(sub_arg.find_first_of(","), 1);
    // cout << sub_arg << endl;
    // aux = sub_arg.substr(0, sub_arg.find_first_of(" "));
    // cout << aux << endl;
    // sub_arg.erase(0, sub_arg.find_first_of(" ")+1);
    // cout << sub_arg << endl;
    // aux = sub_arg.substr(0, sub_arg.find_first_of(" "));
    // cout << sub_arg << endl;


    command = argv[1];
    filename = argv[2];

    if(command == "-p")
        generatePre(filename);
    else if(command == "-o")
        cout << "generate obj\n";
    
  return 0;
}