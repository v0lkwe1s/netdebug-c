#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H

#include "../../Configuration.h"
#include "PostgreSql.h"
#include "Mysql.h"

using namespace std;

class SQLInterface {
public:
    SQLInterface();
    SQLInterface(const SQLInterface& orig);
    virtual ~SQLInterface();
    
    /*If id then Update else then insert*/
    void save(string obj){
        if (obj.find("id") != string::npos){
            //update
        } else {
            //insert
        }
    }
    
    void remove(string obj){
        
    }
    
    void listAll(){
        string sql = "SELECT id, \"user\", passwd FROM public.\"squidUsers\";";
        cout << ps.selectStr(sql) << endl;
    }
    
    void list(int limit){
        
    }
    
    void list(vector<string> params){
        
    }
    
private:
    PostgreSql ps;
//    Mysql ms;
    Str s;

};

#endif /* SQLINTERFACE_H */

