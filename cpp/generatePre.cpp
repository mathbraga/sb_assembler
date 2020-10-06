#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include "trimfunc.cpp"
#include "allCaps.cpp"
using namespace std;

// void treatEQU(fstream &file ,string line){
//     list <string, string> EQUtable;

//     cout << line << ": " << file.tellg() << endl;
// }

void generatePre(string filename){
    fstream infile, outfile, tempfile;
    string line, aux, ext = ".asm";
    char emp = '\0';
    int len = 0, st_flag = 0;
    size_t found;

    infile.open(filename, std::fstream::in | std::fstream::out);

    found = filename.rfind(ext);
    filename.replace(found, ext.length(), ".pre");

    // tempfile.open("tempfile.txt", fstream::in | fstream::out | fstream::trunc);
    outfile.open(filename, fstream::in | fstream::out | fstream::trunc);

    while(getline(infile, line)){ //remove unnecessary
        found = line.find_first_not_of(" \f\n\r\t\v");
        if(found != string::npos){
            line = trim(line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line = removeInBetween(line);
            line = removeComment(line);
            if(line.size() > 0)
                outfile << line << endl;
        }
    }

    // tempfile.clear();
    // tempfile.seekg(0);

    // while(getline(tempfile, line)){ //remove empty lines
    //     line = trimLeft(line);
    //     line = trimRight(line);
    //     outfile << line << endl;
    // }

    infile.close();
    outfile.close();
    // tempfile.close();
}