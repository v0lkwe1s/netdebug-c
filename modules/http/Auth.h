#ifndef AUTH_H
#define AUTH_H

#include "../Str.h"
#include "base64.h"
#include "../database/PostgreSql.h"
using namespace std;

class Auth {
public :
    const string data= "HTTP/1.1 401 OK\r\nContent-Type: text/plain \r\n"
            "WWW-Authenticate: Basic realm=\"My Server\" \r\n"
            "Content-Length: 0 \r\n"
            "Connection: keep-alive\r\n\r\n401";

    int verifyCredentials(string &data){

    if (s.upper(data).find("AUTHORIZATION: BASIC") != std::string::npos) {
        vector<string> buffer = s.split(data, '\n');
            for (unsigned int i = 0; i < buffer.size(); i++) {
                if (s.upper(buffer[i]).find("AUTHORIZATION: BASIC") != std::string::npos) {
                    Base64 b;
                    vector<string> usrPass = s.split(buffer[i], ' ');
                    string requestLogin = (b.decode(usrPass[usrPass.size() -1]));
                    PostgreSql ps;
                    result R = ps.select("SELECT \"UserName\", \"Password\" FROM public.\"Users\";");
                    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                        string ret = (c[0].as<string>() + ":" + c[1].as<string>()).c_str();
                        if (requestLogin == ret) {
                            return 1;
                        }  else {
                        return -1;
                        }
                    }
                }
            }
        } else {
            return 0;
        }
    }

private:

    Str s;
};

#endif /* AUTH_H */

