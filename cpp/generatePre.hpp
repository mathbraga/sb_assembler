#include <iostream>
#include <string>
#include <map>
using namespace std;

void generatePre(string);
void treatEQU(string, fstream&, map<string, string>&);
string subsLabel(string, map<string, string>&);
bool isIF(string line);
int evalIF(string&, fstream&);