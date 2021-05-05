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
#include "Parser.h"

#ifndef IDE_CLIENT_H
#define IDE_CLIENT_H


class Client {
private:
    char buf[4096];
    static QJsonDocument received;
public:

    /*!
     * @brief Getter para la informacion que se obtiene del socket
     * @return QJsonDocument
     */
    static QJsonDocument getReceived();

public:

    /*!
     * @brief Se encarga de levantar el socket y realizar la recepcion/envio de mensajes
     */
    void Start();
};


#endif //IDE_CLIENT_H
