#ifndef SSLSOCKET_H
#define SSLSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <malloc.h>
#include <fcntl.h>
#include <thread>
#include "../http/Nanohttp.h"
#include <sys/wait.h>
#include <thread>
#include "../Str.h"
#include "../../Configuration.h"

using namespace std;

class sslSocket {
public:
    sslSocket();
    sslSocket(const sslSocket& orig);

    void init(unsigned int port);
    int HandleConnections (unsigned int &sock);
    int sendSSL(string &data);
    string recvSSL();
    virtual ~sslSocket();

private:
    int sockfd;
    char buffer[2048];
    int n;
    SSL_CTX *ctx;
    SSL *ssl;

    Config cfg;
    Str s;

    const string nonSSLErr = "HTTP/1.1 308 OK\r\nConnection: close\r\n\r\n"
    "<html><head><meta http-equiv=\"refresh\" content=\"0;"
    "URL=https://192.168.1.250:5555/\" /></head>"
    "<body>REDIRECIONANDO...</body></html>";

    void initSSL(string certificate, string key) {
        SSL_load_error_strings();
        //OpenSSL_add_ssl_algorithms();
        //OpenSSL_add_all_algorithms();
        //OpenSSL_add_all_ciphers();
        //OpenSSL_add_all_digests();

        SSL_library_init();

        const SSL_METHOD *method = TLS_server_method();

        ctx = SSL_CTX_new(method);

        SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);
        SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_OFF);
        SSL_CTX_set_options(ctx, SSL_MODE_AUTO_RETRY );
        SSL_CTX_use_certificate_file(ctx, certificate.c_str(), SSL_FILETYPE_PEM);
        SSL_CTX_use_PrivateKey_file(ctx, key.c_str(), SSL_FILETYPE_PEM);

        ERR_print_errors_fp(stderr);
    }
};

#endif /* SSLSOCKET_H */
