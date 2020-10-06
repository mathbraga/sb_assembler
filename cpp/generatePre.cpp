#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "trimfunc.cpp"
using namespace std;

void generatePre(string filename){
    fstream infile, outfile, tempfile;
    string line, line_trimR, line_trimL, ext = ".asm";
    size_t found;

    infile.open(filename, std::fstream::in | std::fstream::out);

    found = filename.rfind(ext);
    filename.replace(found, ext.length(), ".pre");

    // tempfile.open("tempfile.txt", fstream::in | fstream::out | fstream::trunc);
    outfile.open(filename, fstream::in | fstream::out | fstream::trunc);

    while(getline(infile, line)){ //remove empty lines
        found = line.find_first_not_of(" \f\n\r\t\v");
        if(found != string::npos){
            line = trim(line);
            replace(line.begin(), line.end(), '\t', '\0');
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