#ifndef MASVMETHODS_H
#define MASVMETHODS_H

#include "../Str.h"
#include "../database/PostgreSql.h"
#include "base64.h"

using namespace std;

class MasvMethods {
public:
    MasvMethods();
    MasvMethods(const MasvMethods& orig);
    string getData(string data);
    string psql(string &data);
    virtual ~MasvMethods();

private:
    Str s;
    Config cfg;
    Base64 b64;

};

#endif /* MASVMETHODS_H */
