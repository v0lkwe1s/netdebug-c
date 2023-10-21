#ifndef NANOHTTP_H
#define NANOHTTP_H

#include "base64.h"
#include "MType.h"
#include "../Str.h"
#include "Auth.h"
#include "Masv.h"

class Nanohttp {
public:
    Nanohttp();
    Nanohttp(const Nanohttp& orig);
    Nanohttp(string &data);
    string shttp(string data);
    string route(string data);
    string head(string data);
    string post(string& data);
    string get(string& data);
    string put (string data);
    string delete_ (string data);
    string connect(string data);
    string getMimeType();
    string rest();
    string base64_decript(string encoded);
    string base64_encript(string decoded);
    void sendFile();
    void genericHeader();
    string getWebRootDirectory() const;
    void setWebRootDirectory(string webRootDirectory);

    virtual ~Nanohttp();

private:
    Str s;
    void setParams();
    void setParams(string errorCode);
    string getUrlPath(string url){
        vector<string> path;
        path = s.split(s.subString(url, "\n"), ' ');
//        if (path.size() < 3 ){
//            return path[0];
//        }
//        if ((path[1][strlen(path[1].c_str()) - 1]) == '/') {
//            path[1][strlen(path[1].c_str()) - 1] = ' ';
//        }
//       path[1] = s.subString(path[1].c_str(), " ");
        return path[1];
    }
    void error(){
        this->data = "HTTP/1.1 500 OK\r\n";
        this->data += "Access-Control-Allow-Headers: Content-Type, X-Requested-With \r\n";
        this->data += "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS \r\n";
        this->data += "Access-Control-Allow-Origin: * \r\n";
        this->data += "Content-Type: text/plain \r\n";
        this->data += "Connection: close\r\n\r\n";
        this->data += "ERROR 404/500 - NOT FOUND/SERVER ERROR";
    }
    vector<string> line;
    string data;
    string path;
    Config cfg;
    Auth auth;
};

#endif /* NANOHTTP_H */
