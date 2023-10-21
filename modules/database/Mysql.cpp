#include "Mysql.h"
#define MYCPPCONN_STATIC_MYSQL_VERSION = 4.0.26

Mysql::Mysql() {

    connectionProperties["hostName"] = sql::SQLString("tcp://192.168.1.3:3306");
    //connectionProperties["hostName"] = sql::SQLString("tcp://192.168.1.15:3328");
    connectionProperties["userName"] = sql::SQLString("dummy");
    connectionProperties["password"] = sql::SQLString("123456big");
    //connectionProperties["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;
    //connectionProperties["OPT_CAN_HANDLE_EXPIRED_PASSWORDS"]= true;
    //connectionProperties["preInit"]= sql::SQLString("ALTER USER 'dummy' IDENTIFIED BY '123456big';");
    //connectionProperties["OPT_RECONNECT"] = true;
    //connectionProperties["CLIENT_IGNORE_SIGPIPE"] = true;
    //connectionProperties["CLIENT_IGNORE_SPACE"] = true;
    //connectionProperties["DMYSQLCPPCONN_TRACE_ENABLE"] = true;


    connectionProperties["useLegacyAuth"] = true;
    //connectionProperties["MYSQL_DEFAULT_AUTH"] = true;
    connectionProperties["MYSQL_SECURE_AUTH"] = false;
    //connectionProperties["OPT_IGNORE_SIGPIPE"] = true;
    connectionProperties["OPT_ENABLE_CLEARTEXT_PLUGIN"] = true;
    cout << "InitDriver";
    driver = get_driver_instance();
    cout << "Ok\r\n";


    cout << "Connect" << endl;
    cout << "unix:///sistemaBig/var/run/mysqld/mysqld.sock" << endl;
    con = driver->connect(connectionProperties);

    //cout << con->isClosed();
//    cout << con->getWarnings();

    //con->clearWarnings();
    cout << con->getClientInfo() << endl;
    cout << "setSchema";
    con->setSchema("gerente");

}

Mysql::Mysql(const Mysql& orig) {
}
ResultSet* Mysql::select(string sql) {
        Statement *stmt = con->createStatement();
        ResultSet *res = stmt->executeQuery(sql);
        return res;
}
/*
ResultSet* res = select(string sql);
    while (res->next()) {
        cout << res->getString(1) << endl;
    }
*/
void Mysql::execute(string sql) {
    PreparedStatement *pstmt = con->prepareStatement(sql);
    //pstmt->executeUpdate();
}
Mysql::~Mysql() {
  delete con;
}
