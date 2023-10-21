#include "sslSocket.h"

sslSocket::sslSocket() {}
sslSocket::sslSocket(const sslSocket& orig) {}

void sslSocket::init(unsigned int port) {
    initSSL(cfg.GetCertificate(), cfg.GetCertificateKey());

   if (SSL_CTX_up_ref(ctx) == 0 ){
        perror("SSL CTX or failure");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 serv_addr, cli_addr;
    try {
        sockfd = socket(AF_INET6, SOCK_STREAM , 0);
        unsigned long int on = 1;
        setsockopt( sockfd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR , (const char*) &on, sizeof (on));
        memset( (char *) &serv_addr, 0, sizeof(serv_addr));

        serv_addr.sin6_family = AF_INET6;
        serv_addr.sin6_addr = in6addr_any;
        serv_addr.sin6_port = htons(port);

        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1 ) exit(EXIT_FAILURE);

        listen(sockfd, 32);
    } catch (exception ex){
        perror(ex.what());
    }
    for (;;) {
        try {
            unsigned int len = sizeof(uint8_t);
            unsigned int newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,  &len);
            pid_t pid =  fork();
            switch(pid) {
                case 0:
                    exit(HandleConnections(newsockfd));
                case -1:
                    perror( "fork" );
                    exit(-1);
                default:
                    signal(SIGCHLD, SIG_IGN);
                    break;
            }
            close(newsockfd);
        } catch (exception ex) {
            perror(ex.what());
        }
    }
    close(sockfd);
}

int sslSocket::HandleConnections(unsigned int& sock) {
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    if(SSL_get_fd(ssl) < 0) return -1;
    switch(SSL_accept(ssl)) {
        case -1 :
            send(sock, nonSSLErr.c_str(), nonSSLErr.length(), 0);
            return -1;
        case  1 :
            string data = recvSSL();
            if (data.find("HTTP/1.") != string::npos)
                Nanohttp nh(data);
            sendSSL(data);
            return 1;
    }

    return 0;
}

int sslSocket::sendSSL(string &data) {
    return SSL_write(ssl, data.c_str(), data.length());
}

string sslSocket::recvSSL() {
    string data ="";
    unsigned long bytes = 0;
    unsigned int r = sizeof(buffer);
    for(;;) {
        memset(buffer, 0, sizeof(buffer));
        r = SSL_read(ssl, buffer, r);
        errno = SSL_get_error(ssl, r);
        data+=buffer;
        bytes+=r;
        switch (errno) {
            case SSL_ERROR_NONE:
                if (r < sizeof(buffer) && SSL_pending(ssl) == 0) {
                    return data;
                }
                break;
        case SSL_ERROR_WANT_READ:
            perror("ssl write error");
            continue;
        case SSL_ERROR_WANT_WRITE:
            perror("ssl write error");
            continue;
        case SSL_ERROR_ZERO_RETURN:
            perror("ssl zero bytes read error");
            exit(EXIT_FAILURE);
        case SSL_ERROR_WANT_CONNECT:
             perror("ssl read error");
             break;
         case SSL_ERROR_WANT_ACCEPT:
             perror("ssl error on accepting connection");
             break;
          case SSL_ERROR_WANT_X509_LOOKUP:
             perror("ssl error invalid X509 cert");
             exit(EXIT_FAILURE);
          case SSL_ERROR_SYSCALL:
             perror("Catastrofic error (SSL_ERROR_SYSCALL)");
             exit(EXIT_FAILURE);
          case SSL_ERROR_SSL:
             perror("ssl error");
             break;
        default:
            continue;
        }
    }
    return data;
}

sslSocket::~sslSocket() {
    SSL_CTX_free(ctx);
    EVP_cleanup();
    SSL_free(ssl);
}
