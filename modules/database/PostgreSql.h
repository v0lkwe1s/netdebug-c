#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <iostream>
#include <pqxx/pqxx>
//#include <cppconn/resultset.h>
#include "../Str.h"
#include "../../Configuration.h"

using namespace pqxx;

class PostgreSql {
public:
    PostgreSql();
    PostgreSql(const PostgreSql& orig);
    result select(string sql);

    string selectStr(string sql);
    void execute(string& sql);
    virtual ~PostgreSql();

private:
    Config cfg;
    Str s;
};
#endif /* POSTGRESQL_H */

