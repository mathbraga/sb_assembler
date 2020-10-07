#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include "generatePre.hpp"
#include "trimfunc.cpp"
#include "allCaps.cpp"
using namespace std;

void generatePre(string filename){
    fstream infile, outfile, tempfile;
    string line, aux, ext = ".asm";
    int len = 0, st_flag = 0, if_flag = 1, size = 0;
    size_t found;
    map<string, string> labelsMap;

    infile.open(filename, std::fstream::in | std::fstream::out);

    found = filename.rfind(ext);
    filename.replace(found, ext.length(), ".pre");

    tempfile.open("tempfile.txt", fstream::in | fstream::out | fstream::trunc);
    outfile.open(filename, fstream::in | fstream::out | fstream::trunc);

    while(getline(infile, line)){ //remove unnecessary
        found = line.find_first_not_of(" \f\n\r\t\v");
        if(found != string::npos){
            line = trim(line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line = removeInBetween(line);
            line = removeComment(line);
            line = allCaps(line);
            if(line.size() > 0)
                tempfile << line << endl;
        }
    }

    tempfile.clear();
    tempfile.seekg(0);

    while(getline(tempfile, line)){
        if(line == "SECTION TEXT")
            st_flag = 1;
        if(!st_flag){
            if((found = line.find(':')) != string::npos){
                treatEQU(line, tempfile, labelsMap);
            }
        }
        else if(st_flag){
            line = subsLabel(line, labelsMap);
            if(isIF(line))
                if_flag = evalIF(line, tempfile);
            if(if_flag){
                if(tempfile.peek() == EOF)
                    outfile << line;
                else
                    outfile << line << endl;
            }
            else if(!if_flag)
                if_flag = 1;
        }
    }

    infile.close();
    outfile.close();
    tempfile.close();
    remove("tempfile.txt");
}

void treatEQU(string line, fstream& file, map<string, string>& labelsMap){
    size_t pos;
    string label, value, equ = " EQU ";

    if((pos = line.find(':')) != string::npos)
        label = line.substr(0, pos);

    if((pos = line.find(equ)) != string::npos)
        value = line.substr(pos + equ.length(), line.length() - pos);
    else{
        getline(file, line);
        value = line.substr(equ.length() - 1, line.length() - (equ.length() - 1));
    }

    labelsMap[label] = value;
}

string subsLabel(string line, map<string, string>& labelsMap){
    string output, ws = " ", token;
    size_t pos = 0, i = 0;
    map<string, string>::iterator key;

    output = line;

    do{
        pos = line.find(ws);
        token = line.substr(0, pos);
        if((key = labelsMap.find(token)) != labelsMap.end())
            output.replace(output.begin() + i, output.begin() + pos, labelsMap[token]);

        line.erase(0, pos + ws.length());
        i = pos + ws.length();
    }while(pos != string::npos);

    return output;
}

bool isIF(string line){
    string ws = " ", token, value;
    size_t pos = 0;

    do{
        pos = line.find(ws);
        token = line.substr(0, pos);
        if(token == "IF"){
            return true;
        }
        line.erase(0, pos + ws.length());
    }while(pos != string::npos);

    return false;
}

int evalIF(string& line, fstream& file){
    string ws = " ", token;
    size_t pos = 0;
    int value = 0;

    while((pos = line.find(ws)) != string::npos){
        token = line.substr(0, pos);
        line.erase(0, pos + ws.length());
    }

    value = stoi(line);
    getline(file, line);//skip current line

    return value;
}