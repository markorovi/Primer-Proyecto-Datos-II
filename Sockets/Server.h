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
    char buf[4096];
public:

    /*!
     * @brief Se encarga de levantar el servidor el cual estara acargo del el manejo de la memoria
     */
    void Start();
};


#endif //IDE_SERVER_H
