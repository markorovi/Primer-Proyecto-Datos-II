//
// Created by marco on 4/20/21.
//
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "Parser.h"
#ifndef IDE_SERVER_H
#define IDE_SERVER_H


class Server {
private:
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    int clientSockect;
    char buf[4096];
    sockaddr_in hint;
public:
    void Start();
    void Initialize();
};


#endif //IDE_SERVER_H
