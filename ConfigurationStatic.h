#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include "modules/Str.h"

using namespace std;

class Config {
public :
    Config(){
        vector<string> file = s.split(s.getFileText(s.getCurrentPath()+"/netdebug.conf"), '\n');
        for (int i = 0; i < file.size(); i++) {
            //remove linhas comentadas
            if (!file[i].find("#") != std::string::npos) {
                if (file[i].find("debug=") != std::string::npos) {
                    debug = atoi(s.subString(file[i], "debug=").c_str());
                }
                if (file[i].find("squidLog=") != std::string::npos) {
                    squidLogFile = s.subString(file[i], "squidLog=");
                }
                if (file[i].find("webRootDirectory=") != std::string::npos) {
                    webRootDirectory = s.subString(file[i], "webRootDirectory=");
                }
                if (file[i].find("certificate=") != std::string::npos) {
                    certificate = s.subString(file[i], "certificate=");
                }
                if (file[i].find("certificateKey=") != std::string::npos) {
                    certificateKey = s.subString(file[i], "certificateKey=");
                }
                //porta de serviço da aplicação, não confundir com a porta do banco de dados
                if (file[i].find("port=") != std::string::npos) {
                    port = atoi(s.subString(file[i], "port=").c_str());
                }
            }
        }
    }

    static string GetDatabase() {
        if (database == "") SetDatabase();
        return database;
    }

    bool requireAuth() {
        string file = s.getFileText(s.getCurrentPath()+"/netdebug.conf");
        if (file.find("requireAuth") != std::string::npos) {
            return true;
        }
        return false;
    }
    static string certificate;
    static string certificateKey;
    static unsigned int port;

private :
    Str s;

    string debug;
    static string squidLogFile;
    static string database;

    static string dataBaseUser;
    static string dataBaseName;
    static string dataBaseHost;
    static string dataBasePort;
    static string dataBasePasswd;
    static string dataBaseDriver;
    static string webRootDirectory;

    static void SetDatabase() {
        if (dataBaseDriver == "psql"){
            getDb(dataBaseDriver);
            database = "dbname=" + dataBaseName + " user=" + dataBaseUser
                + " password=" + dataBasePasswd + " hostaddr=" + dataBaseHost
                + " port=" + dataBasePort + "";
        }
        if (dataBaseDriver == "mysql"){
            getDb(dataBaseDriver);
            database = "tcp://\"" + dataBaseHost + ":" + dataBasePort + ", \""
                + dataBaseUser + "\", \""  + dataBasePasswd +"\"";
        }
    }


   static void getDb(string driver){
       Str s;
        vector<string> file = s.split(s.getFileText(s.getCurrentPath()+"/netdebug.conf"), '\n');
        for (int i = 0; i < file.size(); i++) {
            if (file[i].find("databaseDriver=") != std::string::npos) {
                dataBaseDriver = (s.subString(file[i], "databaseDriver="));
            }
            if (dataBaseDriver == driver) {
                if (file[i].find("databaseHost=") != std::string::npos) {
                    dataBaseDriver = (s.subString(file[i], "databaseHost="));
                }
                if (file[i].find("databasePort=") != std::string::npos) {
                    dataBasePort = (s.subString(file[i], "databasePort="));
                }
                if (file[i].find("dataBaseName=") != std::string::npos) {
                    dataBaseName = (s.subString(file[i], "dataBaseName="));
                }
                if (file[i].find("dataBaseUser=") != std::string::npos) {
                    dataBaseUser = (s.subString(file[i], "dataBaseUser="));
                }
                if (file[i].find("databasePasswd=") != std::string::npos) {
                    dataBasePasswd = (s.subString(file[i], "databasePasswd="));
                }
            }
        }
    }

};

#endif /* CONFIG_H */
