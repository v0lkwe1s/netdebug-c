#include <cstdlib>
#include "modules/socket/sslSocket.h"
#include "Configuration.h"
#include "modules/database/PostgreSql.h"
#include "modules/database/Mysql.h"
#include <exception>

using namespace std;

void startServer();

int main(int argc, char** argv) {

    try {
        Mysql mysql;
        ResultSet* res = mysql.select("SHOW databases;");
        //mysql.con->setSchema("gerente");
        //string data = "select * from produto limit 1";
        //ResultSet* res = mysql.select(data);
        while (res->next()) {
            cout << res->getString(1) << endl;
            //cout << res->getString(2) << endl;
           // cout << res->getString(3) << endl;
        }

    } catch (SQLException e){
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        /* what() (derived from std::runtime_error) fetches error message */
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

startServer();
//    thread server(startServer);
//    server.join();

    return 0;
}
void startServer(){
    sslSocket server;
    Config config;
    //server.init(5556);
    server.init(config.GetPort());
}
