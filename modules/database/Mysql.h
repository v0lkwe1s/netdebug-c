#ifndef MYSQL_H
#define MYSQL_H

#include <string>

#include "mysql-cppconn-8/jdbc/mysql_connection.h"

#include <mysql-cppconn-8/jdbc/cppconn/driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/exception.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>

using namespace sql;
using namespace std;

#include "../../Configuration.h"
class Mysql {
public:

    Mysql();
    ResultSet *select(string sql);
    void execute(string sql);
    sql::Connection *con;
    Mysql(const Mysql& orig);
    virtual ~Mysql();

private:
    Config cfg;
    Driver *driver;
    ConnectOptionsMap connectionProperties;
};

#endif /* MYSQL_H */

