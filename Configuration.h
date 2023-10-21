#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include <string>
#include "modules/Str.h"

using namespace std;

class Config {
public :
    Config(){
        vector<string> file = s.split(s.getFileText(s.getCurrentPath()+"/netdebug.conf"), '\n');
        for (unsigned int i = 0; i < file.size(); i++) {
            //remove linhas comentadas
            if (file[i].find("#") == std::string::npos) {
                if (file[i].find("debug=") != std::string::npos) {
                    this->debug = atoi(s.subString(file[i], "debug=").c_str());
                }
                if (file[i].find("squidLog=") != std::string::npos) {
                    this->squidLogFile = s.subString(file[i], "squidLog=");
                }
                if (file[i].find("webRootDirectory=") != std::string::npos) {
		    //Absolute path
                    this->webRootDirectory = s.subString(file[i], "webRootDirectory=");
                }
                if (file[i].find("certificate=") != std::string::npos) {
		    //relative path
                    this->certificate = s.getCurrentPath() + "/" + s.subString(file[i], "certificate=");
                }
                if (file[i].find("certificateKey=") != std::string::npos) {
		    //relative path
                    this->certificateKey =  s.getCurrentPath() + "/" + s.subString(file[i], "certificateKey=");
                }
                //porta de serviço da aplicação, não confundir com a porta do banco de dados
                if (file[i].find("port=") != std::string::npos) {
                    this->port = atoi(s.subString(file[i], "port=").c_str());
                }
                if (debug == 10){
                    cout << file[i] << endl;
                }
            }
        }
    }

    void SetDataBaseDriver(string dataBaseDriver) {this->dataBaseDriver = dataBaseDriver; }
    string GetCertificate() const {return certificate;}
    string GetCertificateKey() const {return certificateKey;}
    string GetSquidLogFile() const {return squidLogFile;}
    string GetWebRootDirectory() const {return webRootDirectory;}
    string GetDataBaseDriver() const {return dataBaseDriver; }
    string GetDataBaseHost() const { return dataBaseHost; }
    void SetDataBaseHost(string dataBaseHost) {this->dataBaseHost = dataBaseHost; }
    string GetDataBaseName() const {return dataBaseName; }
    void SetDataBaseName(string dataBaseName) {this->dataBaseName = dataBaseName;}
    string GetDataBasePasswd() const { return dataBasePasswd;}
    void SetDataBasePasswd(string dataBasePasswd) {this->dataBasePasswd = dataBasePasswd; }
    string GetDataBasePort() const {return dataBasePort; }
    void SetDataBasePort(string dataBasePort) { this->dataBasePort = dataBasePort; }
    string GetDataBaseUser() const { return dataBaseUser; }
    void SetDataBaseUser(string dataBaseUser) { this->dataBaseUser = dataBaseUser;}
    string GetDatabase() const { return database;}
    int GetDebug() const { return debug; }
    void SetDebug(int debug) { this->debug = debug; }
    int GetPort() const {return port;}
    void SetPort(int port) {this->port = port;}

    void SetDatabase() {
        if (this->GetDataBaseDriver() == "psql"){
            this->getDb(GetDataBaseDriver());
            database = "dbname=" + this->GetDataBaseName() + " user=" + this->GetDataBaseUser()
                + " password=" + this->GetDataBasePasswd() + " hostaddr=" + this->GetDataBaseHost()
                + " port=" + this->GetDataBasePort() + "";
        }
        if (this->GetDataBaseDriver() == "mysql"){
            this->getDb(GetDataBaseDriver());
            database = "tcp://\"" + this->GetDataBaseHost() + ":" +  this->GetDataBasePort() + ", \""
                + this->GetDataBaseUser() + "\", \""  + this->GetDataBasePasswd()+"\"";
        }
    }

    bool requireAuth() {
        string file = s.getFileText(s.getCurrentPath()+"/netdebug.conf");
        if (file.find("requireAuth") != std::string::npos) {
            return true;
        }
        return false;
    }

private :
    Str s;
    int port;
    string webRootDirectory;
    string squidLogFile;
    string certificate;
    string certificateKey;
    string dataBaseName;
    string dataBaseHost;
    string dataBasePort;
    string dataBasePasswd;
    string dataBaseUser;
    string dataBaseDriver;
    string database;
    int debug = 0;

    void getDb(string driver){

        vector<string> file = s.split(s.getFileText(s.getCurrentPath()+"/netdebug.conf"), '\n');
        for (unsigned int i = 0; i < file.size(); i++) {
            if (file[i].find("databaseDriver=") != std::string::npos) {
                this->SetDataBaseDriver(s.subString(file[i], "databaseDriver="));
            }
            if (this->GetDataBaseDriver() == driver) {
                if (file[i].find("databaseHost=") != std::string::npos) {
                    this->SetDataBaseHost(s.subString(file[i], "databaseHost="));
                }
                if (file[i].find("databasePort=") != std::string::npos) {
                    this->SetDataBasePort(s.subString(file[i], "databasePort="));
                }
                if (file[i].find("dataBaseName=") != std::string::npos) {
                    this->SetDataBaseName(s.subString(file[i], "dataBaseName="));
                }
                if (file[i].find("dataBaseUser=") != std::string::npos) {
                    this->SetDataBaseUser(s.subString(file[i], "dataBaseUser="));
                }
                if (file[i].find("databasePasswd=") != std::string::npos) {
                    this->SetDataBasePasswd(s.subString(file[i], "databasePasswd="));
                }
            }
        }
    }

};

#endif /* CONFIG_H */
