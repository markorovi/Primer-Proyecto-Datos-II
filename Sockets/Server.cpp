//
// Created by marco on 4/20/21.
//
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <sstream>
#include "../Memory/Memory.h"
#include "Server.h"




void Server::Start() {
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));

// Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

// Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSockect = accept(listening, (sockaddr*)&client, &clientSize);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

// Close listening socket
    close(listening);
    while (true){
        memset(this->buf, 0, 4096);

// Wait for client to send data
        int bytesReceived = recv(clientSockect, this->buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Error in recv(). Quitting" << std::endl;

            break;
        }

        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected " << std::endl;
            close(clientSockect);
            this->Start();
            break;
        }
        QJsonDocument doc = Parser::ReturnJson(std::string(this->buf, 0, bytesReceived).c_str()); //Devolver lo que llego por el socket a json
        QJsonDocument toReturn;
        if (Parser::ReturnStringValueFromJson(doc, "toDo") == "assign"){
            Memory::get_instance()->Need_Memory(Parser::ReturnStringValueFromJson(doc, "type"), Parser::ReturnStringValueFromJson(doc, "value"), Parser::ReturnStringValueFromJson(doc, "name"));
            void *address = Memory::get_instance()->getInUse().GetHead()->GetAddress();
            std::stringstream ss;
            ss << address;
            std::string strAddress = ss.str();
            toReturn.setObject(Parser::CreateJsonObj_Address(Parser::ReturnStringValueFromJson(doc, "type"), Parser::ReturnStringValueFromJson(doc, "name"), Parser::ReturnStringValueFromJson(doc, "value"), strAddress));
        } else if (Parser::ReturnStringValueFromJson(doc, "toDo") == "nothing"){
            toReturn.setObject(Parser::Nothing());
        }

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
//        std::cout<<test;
//        this->buf = strJson(doc.toJson(QJsonDocument::Compact));
//
//        QJsonDocument aaaa = QJsonDocument::fromJson(strJson.toUtf8());
//
//        std::cout << std::string(this->buf, 0, bytesReceived)<< "impresion final" << std::endl;
//
// Echo message back to client
//        send(this->clientSockect, prueba, test.size(), 0);
        std::cout<<Parser::ReturnChar(toReturn).c_str()<<std::endl;
        send(clientSockect, Parser::ReturnChar(toReturn).c_str(), Parser::ReturnChar(toReturn).size() + 1, 0);
    }

// Close the socket
    close(clientSockect);

}
