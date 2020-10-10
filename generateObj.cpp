#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "generateObj.hpp"
using namespace std;

void generateObj(string filename){
    fstream infile, outfile;
    string line, ext = ".pre", inst, op1, op2;
    size_t found;
    map<string, string> opcode;
    map<string, int> inst_size;
    map<string, int> labels;
    map<string, int> ops;
    map<string, int>::iterator search_size;
    int pos_count=0, line_count=1, n_op = 0;
    size_t pos= 0;

    createMaps(opcode, inst_size, ops);
    
    infile.open(filename, std::fstream::in | std::fstream::out);

    if(!infile){
        cerr << "File not found." << endl;
        return;
    }

    found = filename.rfind(ext);
    filename.replace(found, ext.length(), ".obj");

    outfile.open(filename, fstream::in | fstream::out | fstream::trunc);

    while(getline(infile, line)){ //first transition
        if((line != "SECTION TEXT") && (line != "SECTION DATA")){
            if((pos = line.find(":")) != string::npos){// if line has a label
                labels[line.substr(0, pos)] = pos_count;
                line.erase(0, pos+2);
            }
            if(((search_size = inst_size.find(line)) != inst_size.end())) // if line is a SPACE or STOP instruction (label has been removed from the line at this point)
                pos_count = pos_count + inst_size[line];

            while((pos = line.find(" ")) != string::npos){
                inst = line.substr(0, pos);
                if((search_size = inst_size.find(inst)) != inst_size.end())
                    pos_count = pos_count + inst_size[inst];
                
                line.erase(0, pos+1);
            }
        }
    }

    infile.clear();
    infile.seekg(0);

    while(getline(infile, line)){
        if((line != "SECTION TEXT") && (line != "SECTION DATA")){
            if((pos = line.find(":")) != string::npos)// remove label from line
                line.erase(0, pos+2);

            inst = line.substr(0, line.find_first_of(" "));
            if((search_size = inst_size.find(inst)) != inst_size.end()){
                pos_count = pos_count + inst_size[inst];
                line.replace(0, inst.length(), opcode[inst]);

                if(inst == "CONST")
                    line.erase(0, line.find_first_of(" ")+1);
            }

            n_op = ops[inst];
            if(n_op == 1){
                op1 = line.substr(line.find_first_of(" ")+1, line.length()-(line.find_first_of(" ")+1));
                if((search_size = labels.find(op1)) != labels.end())
                    line.replace(line.find_first_of(" ")+1, op1.length(), to_string(labels[op1]));
            }

            else if(n_op == 2){
                op1 = line.substr(line.find_first_of(" ")+1, line.find_first_of(",")-(line.find_first_of(" ")+1));
                op2 = line.substr(line.find_first_of(",")+2, line.length()-(line.find_first_of(",")+2));
                if((search_size = labels.find(op1)) != labels.end())
                    line.replace(line.find_first_of(" ")+1, op1.length(), to_string(labels[op1]));
                if((search_size = labels.find(op2)) != labels.end()){
                    line.replace(line.find_first_of(",")+2, op2.length(), to_string(labels[op2]));
                    line.erase(line.find_first_of(","), 1);
                }
            }

            if(line.size() > 0){
                if(infile.peek() == EOF)
                    outfile << line;
                else
                    outfile << line << " ";
            }
        }
    }

    infile.close();
    outfile.close();

    opcode.clear();
    inst_size.clear();
    ops.clear();
    labels.clear();
}

void createMaps(map<string, string>& opcode, map<string, int>& inst_size, map<string, int>& ops){
    opcode["ADD"]="1";
    opcode["SUB"]="2";
    opcode["MULT"]="3";
    opcode["DIV"]="4";
    opcode["JMP"]="5";
    opcode["JMPN"]="6";
    opcode["JMPP"]="7";
    opcode["JMPZ"]="8";
    opcode["COPY"]="9";
    opcode["LOAD"]="10";
    opcode["STORE"]="11";
    opcode["INPUT"]="12";
    opcode["OUTPUT"]="13";
    opcode["STOP"]="14";
    opcode["SPACE"]="00";
    opcode["CONST"]="";

    inst_size["ADD"]=2;
    inst_size["SUB"]=2;
    inst_size["MULT"]=2;
    inst_size["DIV"]=2;
    inst_size["JMP"]=2;
    inst_size["JMPN"]=2;
    inst_size["JMPP"]=2;
    inst_size["JMPZ"]=2;
    inst_size["COPY"]=3;
    inst_size["LOAD"]=2;
    inst_size["STORE"]=2;
    inst_size["INPUT"]=2;
    inst_size["OUTPUT"]=2;
    inst_size["STOP"]=1;
    inst_size["SPACE"]=1;
    inst_size["CONST"]=1;

    ops["ADD"]=1;
    ops["SUB"]=1;
    ops["MULT"]=1;
    ops["DIV"]=1;
    ops["JMP"]=1;
    ops["JMPN"]=1;
    ops["JMPP"]=1;
    ops["JMPZ"]=1;
    ops["COPY"]=2;
    ops["LOAD"]=1;
    ops["STORE"]=1;
    ops["INPUT"]=1;
    ops["OUTPUT"]=1;
    ops["STOP"]=0;
    ops["SPACE"]=0;
}

// string translateInst(string line, int& pos_count, int& line_count){

// }