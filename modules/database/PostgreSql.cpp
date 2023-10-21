#include "PostgreSql.h"

PostgreSql::PostgreSql() {
    //allow use multiple databases;
    cfg.SetDataBaseDriver("psql");
    cfg.SetDatabase();
}

PostgreSql::~PostgreSql() {}

result PostgreSql::select(string sql) {
    try {
        connection C(cfg.GetDatabase().c_str());
        if (C.is_open()) {
            nontransaction N(C);
            result R(N.exec(sql.c_str()));
            return R;
        }
    } catch (exception& e) {
        perror(e.what());
    }
    result R;
    return R;
}

string PostgreSql::selectStr(string sql){
    string data= "";
    try {
        connection C(cfg.GetDatabase().c_str());
        if (cfg.GetDebug() > 0) cout << sql << endl;
            nontransaction N(C);
            result R(N.exec(sql.c_str()));
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                for (unsigned int i = 0; i < c.size(); i++) {
                    data += c[i].as<string>()+"\n";
                }
            }
        } catch (const pqxx::sql_error &e) {
            perror(e.what());
            return e.what();
            //e.query()
        } catch(exception ex) {
            perror(ex.what());
            return ex.what();
        }
    return data;
}

void PostgreSql::execute(string& sql) {
    try {
        connection C(cfg.GetDatabase());
        if (C.is_open()) {
            work W(C);
            W.exec(sql.c_str());
            W.commit();
            C.disconnect();
        }
    } catch (const std::exception &e) {
        perror(e.what());
    }
}

PostgreSql::PostgreSql(const PostgreSql& orig){}
