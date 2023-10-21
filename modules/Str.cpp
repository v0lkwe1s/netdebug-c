#include "Str.h"

Str::Str() {}
Str::Str(const Str& orig) {}
Str::~Str() {}
string Str::getBashRet(string& comm){
	try {
        FILE *in;
        char buff[512];
        in = popen(comm.c_str(), "r");
        comm = "";
        while (fgets(buff, sizeof(buff), in) != NULL) {
            comm += buff;
        }
        pclose(in);
	} catch (std::bad_alloc& e) {
		cerr << e.what() << endl;
		comm = "Err";
	}
	return comm;
}

void Str::split(const string& s, char c, vector<string>& v) {
    string::size_type i = 0;
    string::size_type j = s.find(c);
    while (j != string::npos) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
        if (j == string::npos) {
            v.push_back(s.substr(i, s.length()));
        }
    }
}
vector<string> Str::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter)) {
	  internal.push_back(tok);
	}
	return internal;
}
string Str::subString(string t, string s) {
    std::string::size_type i = t.find(s);
    if (i != std::string::npos)
        t.erase(i, s.length());
    return t;
}
//por que diabos existe esta função?????
string Str::subString(string t, int begin, int end) {
    t.substr(begin, end);
    return t;
}
string Str::getFileText(string filename) {
    string line;
    string text;
    ifstream myfile;
    myfile.open(filename.c_str());
    try {
        int i = 0;
        if (myfile.is_open()) {
            while (!myfile.eof()) {
                getline(myfile, line);
                text+= line+"\n";
                //@POG
                //if i == 10 and text length == 10, it can be a directory.
                //logik
                //if file has at least 32 lines, and data length 32, it means that file dont have \n in lines,
                //IF file is empty, but this file dont have EOF,
                //the while condition dont get reached, ocurring a infinite loop
                i++;
                if (i == 32 && text.length() == 32 ) throw "301";
           }
            myfile.close();
            return text;
        }
    } catch (string& ex) {
        return ex;
    }
    return "500";
}

string Str::getCurrentPath(){
	char cwd[1024];
	string path = getcwd(cwd, sizeof(cwd));
	return path;
}
string Str::numberToStr(double n) {
    stringstream ss;
	ss << n;
	return ss.str();
}
void Str::createFileText(string text, string file){
	ofstream out;
	out.open(file.c_str());
	out << text;
	out.flush();
	out.close();
}
/*Retorna ou altera o texto dentro da função,
 *parametros: \t
 * subject : texto a ser procurado \n
 * search : texto a ser substituido por replace \n
 */
string Str::replace(string& subject, const string& search, const string& replaceTo){
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replaceTo);
		pos += replaceTo.length();
	}
	return subject;
}
string Str::getTimestamp(){
	time_t t = time(0);
	struct tm * now = localtime(& t);
	string dt = (numberToStr(now->tm_year + 1900));
	dt += '-';
	dt += (numberToStr(now->tm_mon + 1));
	dt += '-';
	dt += numberToStr(now->tm_mday);
	dt += ' ';
	dt += numberToStr(now->tm_hour);
	dt += ':';
	dt += numberToStr(now->tm_min);
	dt += ':';
	dt += numberToStr(now->tm_sec);
	return dt;
}
string Str::getTimestamp(string patern){
    if (patern.length() == 0) return getTimestamp();
	time_t t = time(0);
	struct tm * now = localtime(& t);
	string date = replace(patern,"yyyy", numberToStr(now->tm_year + 1900));
    date = replace(patern,"MM", numberToStr(now->tm_mon + 1));
    date = replace(patern, "dd", numberToStr(now->tm_mday));
    date = replace(patern, "hh", numberToStr(now->tm_hour));
    date = replace(patern, "mm", numberToStr(now->tm_min));
    date = replace(patern, "ss", numberToStr(now->tm_sec));
	return date;
}
void Str::c_buffer_str(char* charBuffer, int RCVBUFSIZE, string& data) {
    for (int i = 2; i < RCVBUFSIZE; i++) {
        data += charBuffer[i];
    }
}
void Str::toUpper(string& str) {
    string buffer =str;
    str="";
    for (unsigned int i = 0; i < buffer.length(); i++) {
        str+= toupper(buffer[i]);
    }
}
string Str::upper(string str) {
    string buffer =str;
    for (unsigned int i = 0; i < str.length(); i++) {
        buffer+= toupper(str[i]);
    }
    return buffer;
}
const char* Str::sqlitePath() {
    vector<string> config = split(getFileText("netdebug.conf"), '\n');
    string path = "";
    for (unsigned int i = 0; i < config.size(); i++) {
        if ((config[i].find("sqlite")) != std::string::npos) {
            vector<string> colunm = split(config[i], '=');
            path = colunm[1];
        }
    }
    return path.c_str();
}
