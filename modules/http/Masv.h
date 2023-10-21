#ifndef MASV_H
#define MASV_H

#include <string>
#include "../../Configuration.h"
#include "../Str.h"
#include "MasvMethods.h"

using namespace std;

class Masv {
public:
    Masv();
    Masv(const Masv& orig);

    void getData(string &file, string &data){

    MasvMethods mv;

    //Evita a procura de tags em strings contentdo imagens em png.
//    if (data.find("data:image/png;base64,") != std::string::npos){
//        vector<string> paramValue = s.split(data,'=');
//        data = s.replace(file,
//            "$_"+s.split(paramValue[0], '?')[1],
//            mv.getData(paramValue[1]));
//        data = s.replace(data, "<@#", "");
//        data = s.replace(data, "@/>", "");
//        return;
//    }
    vector<string> col = getParam(s.split(data,'\n'));
    //replace file tags with http header content
    for (unsigned int i = 0; i < col.size(); i++){
        string coll = "$_" + col[i].substr(0, col[i].find("="));
        s.replace(file, coll, col[i].substr(col[i].find("=") + 1));
    }
    //create array of tags
    string buffer ="";
    for (unsigned int i = 0; i < file.length(); i++) {
        buffer += file.at(i);
        if (buffer.find("<@#") != string::npos){
            buffer.erase(0, buffer.find("<@#"));
            if ((buffer.find("@/>")!= string::npos) == 1){
                tags.push_back(buffer.substr(3, buffer.length() -6));
                buffer.clear();
            }
        }
    }
    for (unsigned int i = 0; i < tags.size(); i++) {
        string buffer = tags[i];
        while (buffer.find("$_") != string::npos){
            size_t found = tags[i].find_last_of("abcdefghijklmnopqrstuvwxyz1234567890_\n\t\0 ");
            string removeTag = tags[i].substr(tags[i].find("$_"), tags[i][found]);
            try {
                buffer = s.replace(buffer,
                    buffer.substr(
                        (buffer.find("/*")),
                        (buffer.find("*/")+2-buffer.find("/*"))
                    ),
                "");
            } catch (exception ex){
                cerr << "Erro->" << ex.what() << endl;
                data = "501";
                return;
            }
            //string req = mv.getData(buffer);
           // data = s.replace(file, "<@#"+tags[i]+"@/>", req);
        }
        buffer = s.replace(buffer,"/*","");
        buffer = s.replace(buffer,"*/","");
        string result = mv.getData(buffer);
        data = s.replace(file,"<@#"+tags[i]+"@/>",result);
    }
}

   string getDate();

    virtual ~Masv();

private:
    vector<string> tags;
    Config cfg;
    Str s;
    vector<string> getParam(vector<string> data){
        vector<string> get, post, result;
        //RFC2616 Sec 3 -> HTTP METHOD is on first line
        if (data[0].find("GET /") != std::string::npos){
            vector<string> line = s.split(data[0],' ');
            get = s.split(line[1].substr(line[1].find("?") +1),'&');
        }
        //RFC2616 Sec 3 -> HTTP METHOD is on first line
        //POST PARAMETERS IS ON LAST LINE
        if (
            (data[0].find("POST /") != std::string::npos) or
            (data[data.size() - 1].find("&") != string::npos)
        ) post =  s.split(data[data.size() - 1],'&');

        result.reserve(get.size() + post.size());
        result.insert(result.end(), get.begin(), get.end());
        result.insert(result.end(), post.begin(), post.end());
        return result;
    }
};


#endif /* MASV_H */
