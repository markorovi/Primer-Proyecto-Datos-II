//
// Created by marco on 4/20/21.
//
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "Server.h"

void Server::Initialize() {
// Bind the ip address and port to a socket
    this->hint.sin_family = AF_INET;
    this->hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &this->hint.sin_addr);

    bind(this->listening, (sockaddr*)&this->hint, sizeof(this->hint));

// Tell Winsock the socket is for listening
    listen(this->listening, SOMAXCONN);

// Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    this->clientSockect = accept(this->listening, (sockaddr*)&client, &clientSize);

//    char host[NI_MAXHOST];      // Client's remote name
//    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
//
//    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
//    memset(service, 0, NI_MAXSERV);
//
//    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
//    {
//        std::cout << host << " connected on port " << service << std::endl;
//    }
//    else
//    {
//        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
//        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
//    }

// Close listening socket
    close(listening);

// While loop: accept and echo message back to client
//    char buf[4096];
}



void Server::Start() {
    while (true){
        memset(this->buf, 0, 4096);

// Wait for client to send data
        int bytesReceived = recv(this->clientSockect, this->buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Error in recv(). Quitting" << std::endl;
            break;
        }

        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected " << std::endl;
            break;
        }
        QJsonDocument doc2 = Parser::ReturnJson(std::string(this->buf, 0, bytesReceived).c_str()); //Devolver lo que llego por el socket a json
        std::cout<<Parser::ReturnStringValueFromJson(doc2, "toDo"); //Obtener un valor de json
//        QJsonDocument doc;
//        QJsonObject obj;
//        obj["test"] = "respuesta";
//        obj["test1"] = "respuesta1";
//        obj["test2"] = "respuesta2";
//        obj["test3"] = "respuesta3";
//        doc.setObject(obj);
//        QString strJson(doc.toJson(QJsonDocument::Compact));
//        std::string test =  strJson.toUtf8().constData();
//        const void * prueba= test.c_str();
        //std::cout<<test;
        //this->buf = strJson(doc.toJson(QJsonDocument::Compact));

        //QJsonDocument aaaa = QJsonDocument::fromJson(strJson.toUtf8());

        //std::cout << std::string(this->buf, 0, bytesReceived)<< "impresion final" << std::endl;

// Echo message back to client
        //send(this->clientSockect, prueba, test.size(), 0);
        send(this->clientSockect, this->buf, bytesReceived + 1, 0);
    }

// Close the socket
    close(this->clientSockect);
}
