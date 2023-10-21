#include <string>

#include "Nanohttp.h"

using namespace std;
bool debug = false;
bool authorization = false;

Nanohttp::Nanohttp(){}
Nanohttp::Nanohttp(const Nanohttp& orig){}

Nanohttp::Nanohttp(string &data){
    //buffer data
    this->data = data;
    this->path = getUrlPath(this->data);
//    if (cfg.requireAuth()) {
//        Auth a;
//        if (a.verifyCredentials(data) < 1) {
//            return;
//        }
//    }

    /*FIX GOOGLE CHROME ANGULARJS DONT RENDERING OBJECT DATA WHEN HAVE ERROR 404 IN PAGE*/
    if (this->path.find("%7B%7B%20") != std::string::npos) {
        setParams("200 OK");
        data = this->data;
        return ;
    }
    this->path = (this->path.find(".") != std::string::npos)
            ? this->path
            : this->path + "/index.html";

    if (this->data.find("POST") != std::string::npos) {
        data = post(this->data);
        return;
    }
    if (this->data.find("GET") != std::string::npos) {
        data = get(data);
        return;
    }
    data = "HTTP/1.1 501 Not Implemented\r\n";
    data += "Connection: close\r\n\r\n";
    data += "Server Error";
    data = this->data;
}

string Nanohttp::put(string data){return "";}
string Nanohttp::post(string& data){
    data = get(data);
    return data;
}
string Nanohttp::head(string data){return "";}
string Nanohttp::getMimeType(){

	string ret = "text/plain";
	vector<MType> mts;
	MType m;
	m.SetExt(".css");
	m.SetType("text/css");
	mts.push_back(m);
	m.SetExt(".htm");
	m.SetType("text/html");
	mts.push_back(m);
	m.SetExt(".json");
	m.SetType("text/plain");
	mts.push_back(m);
	m.SetExt(".ico");
	m.SetType("image/x-icon");
	mts.push_back(m);
	m.SetExt(".jpg");
	m.SetType("image/jpeg");
	mts.push_back(m);
	m.SetExt(".png");
	m.SetType("image/png");
	mts.push_back(m);
    m.SetExt(".woff2");
	m.SetType("application/font-woff2");
	mts.push_back(m);
    m.SetExt(".ttf");
	m.SetType("application/x-font-TrueType");
    mts.push_back(m);
    m.SetExt(".svg");
    m.SetType("image/svg+xml");
	mts.push_back(m);

	for (unsigned int i = 0; i < mts.size(); i++) {
		if (this->path.find(mts[i].GetExt()) != std::string::npos) {
			return mts[i].GetType();
		}
	}
	return ret;
}
string Nanohttp::get(string& data){
	if (route(data) == "route") return this->data;
	    string filename = this->path;
	if (this->path.find("?") != std::string::npos) {
        filename = s.split(this->path, '?')[0];
	}
	string file = "";
    try {
        file = s.getFileText(cfg.GetWebRootDirectory()+ "/" + filename);
    } catch (char const* ex){
        this->data = "";
        setParams(ex);
        return this->data;
    }

    /*independente do tipo e tamanho do arquivo, estava acionando o interpretador
    /*e travando a conexão até o timeout, e no termino do processamento,
    /* ao devolver a requisição para o cliente, causava um erro de I/O,
    //Bloqueando o fork do processo, Mantendo a cpu aguardando os signais
    //SIGCHLD ou SIG_IGN. */
    if (file.length() < 16384*1024) {//16 Megabytes
        if (file.find("<@#") != std::string::npos){
            Masv masv;
            masv.getData(file, data);
            //alterar para modo multiplo
            file = s.replace(file, "<@#", "");
            file = s.replace(file, "@/>", "");
        }
        this->data = file;
        genericHeader();
    }
	return this->data;
}

void Nanohttp::genericHeader(){
    //deixando em conformidade com a rfc7230
    //https://tools.ietf.org/html/rfc7230#section-3.3.2
    string buffer = this->data;
    setParams();
    this->data += buffer;
}

void Nanohttp::setParams(){
    unsigned long int contentLength = this->data.length();
	this->data = "HTTP/1.1 200 OK\r\n";
	this->data += "Access-Control-Allow-Headers: Content-Type, X-Requested-With \r\n";
	this->data += "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS \r\n";
	this->data += "Access-Control-Allow-Origin: * \r\n";
	this->data += "Content-Type: " + getMimeType() + "\r\n";
	this->data += "Content-Length : " + s.numberToStr(contentLength) + "\r\n";
	this->data += "Connection: close\r\n\r\n";
}

void Nanohttp::setParams(string errorCode){
	this->data = "HTTP/1.1 " + errorCode + "\r\n";
	this->data += "Content-Type: text/plain\r\n";
	this->data += "Connection: close\r\n\r\n";
	this->data += errorCode;
}

void Nanohttp::sendFile(){}

string Nanohttp::delete_(string data){return "";}
string Nanohttp::connect(string data){return "";}

string Nanohttp::route(string data){
    if (this->path.at(this->path.size() -1) == '/'){
        this->path = "/index.html";
        return this->path;
    }
    return this->data;
}

Nanohttp::~Nanohttp(){}
