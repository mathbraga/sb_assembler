#include <iostream>
using namespace std;

inline string trimRight(const string& s, const string& delimiters = " \f\n\r\t\v"){
    return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string trimLeft(const string& s, const string& delimiters = " \f\n\r\t\v"){
  return s.substr(s.find_first_not_of(delimiters));
}

inline string trim(const string& s, const string& delimiters = " \f\n\r\t\v"){
  return trimLeft(trimRight(s, delimiters), delimiters);
}