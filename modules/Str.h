#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <unistd.h>

using namespace std;

class Str {
public:
  Str();
  Str(const Str& orig);
  virtual ~Str();

  void split(const string& s, char c, vector<string>& v);
  vector<string> split(string str, char delimiter);
  string numberToStr(double n);
  string getFileText(string filename);
  string subString(string t, string s);
  string subString(string t, int begin, int end);
  void createFileText(string text, string file);
  string replace(string& subject, const string& search,const string& replaceTo);
  string getCurrentPath();
  string getTimestamp();
  string getTimestamp(string patern);
  string getBashRet(string& comm);
  void c_buffer_str(char* charBuffer, int RCVBUFSIZE, string& data);
  const char* sqlitePath();
  void toUpper(string& str);
  string upper(string str);

private:

};

#endif /* STR_H */
