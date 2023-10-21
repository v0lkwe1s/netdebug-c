#include "MasvMethods.h"

MasvMethods::MasvMethods() {}

MasvMethods::MasvMethods(const MasvMethods& orig) {}

string MasvMethods::getData(string data){
    string buffer ="";
//    for (unsigned long i; data.length(); i++ )
//    {
//        size_t s;
//        size_t f;
//        buffer += data.at(i);
//        if (( s = buffer.find("/*") != string::npos) &&
//            ( f = buffer.find("*/")!= string::npos)) {
//            cout << data.substr(s, f) << endl;
//        }
//    }
    if (data.find("psql:") != string::npos) {
        return psql(data);
    } else if (data.find("date:") != string::npos) {
        data = s.getTimestamp(s.subString(data, "getdate:").c_str());
        data = s.replace(data, " ", "");
        return data;
    } else if (data.find("dash:") != string::npos) {
        string comm = s.subString(data, "dash:").c_str();
        comm = s.replace(comm,"\n","");
        data = s.getBashRet(comm);
        return data;
    } else if (data.find("read:") != string::npos) {
        string comm = s.subString(data, "read:").c_str();
        comm = "cat " + comm;
        comm = s.replace(comm,"\n","");
        data = s.getBashRet(comm);
        return data;
    } else if (data.find("java:") != string::npos) {
        string comm = s.subString(data, "java:").c_str();
        comm = s.replace(comm,"\n","");
        data = s.getBashRet(comm);
        return data;
    } else if (data.find("mysql4:") != string::npos) {
        string comm = s.subString(data, "mysql4:").c_str();
        string buffer = "java -jar StdinMysqlStdout.jar --queries="+ comm;
        data = s.getBashRet(buffer);
        return data;
	} else if (data.find("data:image/png") != string::npos){
        data = s.replace(data, "<@#", "");
        data = s.replace(data, "@/>", "");
        vector<string> head = s.split(data, '\n');
        vector<string> coll = s.split(head.at(0),' ');
        vector<string> file = s.split(coll[0], ',');
        string filePath = cfg.GetWebRootDirectory()+ "tmp/img.png";
        string newFile = b64.decode(file[1]);
        s.createFileText(newFile, filePath);
        string comm = "zbarimg web/tmp/img.png -q";
        string dash = s.getBashRet(comm);

        if (dash.length() < 5){
            comm = "tesseract web/tmp/img.png stdout";
            dash = s.getBashRet(comm);
        } else {
            dash = s.replace(dash,  " ", "");
            dash = s.replace(dash,  "\n", "");
            return data = dash;
        }
        data = ((dash.length() < 5) ? "Err" : dash);
        return data;
    } else {
        data = "404";
    }
    data = "404";
    return data;
}
string MasvMethods::psql(string &data){
    PostgreSql ps;
    //ajustar o paramentro insert para que possa ser inserido com espaço
    //exemplo: psql: insert
    if (data.find("psql:insert") != string::npos) {
        try {
            string sql = s.subString(data, "psql:").c_str();
            ps.execute(sql);
            return "ok";
        } catch(exception ex){
            return ex.what();
        }
    }
    data = ps.selectStr(s.subString(data, "psql:"));
    return data;
}
MasvMethods::~MasvMethods() {}
