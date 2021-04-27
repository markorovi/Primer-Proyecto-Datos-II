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
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int port = 54000;
    std::string ipAddress = "127.0.0.1";
    sockaddr_in hint;
    char buf[4096];
    std::string userInput;
public:
    void Initialize();
    void Start();
};


#endif //IDE_CLIENT_H
