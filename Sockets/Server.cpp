//
// Created by marco on 4/20/21.
//
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <sstream>
#include "../Memory/Memory.h"
#include "Server.h"

///Se encarga de levantar el servidor el cual estara acargo de todo el manejo de la memoria
void Server::Start() {
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    listen(listening, SOMAXCONN);

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSockect = accept(listening, (sockaddr*)&client, &clientSize);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    close(listening);
    while (true){
        memset(this->buf, 0, 4096);

        int bytesReceived = recv(clientSockect, this->buf, 4096, 0);
        if (bytesReceived == -1){
            std::cerr << "Error in recv(). Quitting" << std::endl;
            break;
        }

        if (bytesReceived == 0){
            std::cout << "Client disconnected " << std::endl;
            close(clientSockect);
            this->Start();
            break;
        }
        QJsonDocument doc = Parser::ReturnJson(std::string(this->buf, 0, bytesReceived).c_str()); //Devolver lo que llego por el socket a json
        QJsonDocument toReturn;
        if (Parser::ReturnStringValueFromJson(doc, "toDo") == "assign"){
            std::cout<<Parser::ReturnStringValueFromJson(doc, "toDo")<<std::endl;
            Memory::get_instance()->Need_Memory(Parser::ReturnStringValueFromJson(doc, "type"), Parser::ReturnStringValueFromJson(doc, "value"), Parser::ReturnStringValueFromJson(doc, "name"));
            if(Memory::get_instance()->getInUse().exists(Parser::ReturnStringValueFromJson(doc, "name"), Memory::get_instance()->getInUse().GetHead())){
                void *address = Memory::get_instance()->getInUse().returnAddress(Parser::ReturnStringValueFromJson(doc, "name"), Memory::get_instance()->getInUse().GetHead());
                std::stringstream ss;
                ss << address;
                std::string strAddress = ss.str();
                toReturn.setObject(Parser::CreateJsonObj_Address(Parser::ReturnStringValueFromJson(doc, "type"), Parser::ReturnStringValueFromJson(doc, "name"), Parser::ReturnStringValueFromJson(doc, "value"), strAddress));

            } else {
                void *address = Memory::get_instance()->getInUse().GetHead()->GetAddress();
                std::stringstream ss;
                ss << address;
                std::string strAddress = ss.str();
                toReturn.setObject(Parser::CreateJsonObj_Address(Parser::ReturnStringValueFromJson(doc, "type"), Parser::ReturnStringValueFromJson(doc, "name"), Parser::ReturnStringValueFromJson(doc, "value"), strAddress));
            }
        } else if (Parser::ReturnStringValueFromJson(doc, "toDo") == "free") {
            Memory::get_instance()->Freeing_Memory(Parser::ReturnStringValueFromJson(doc, "name"));
            toReturn.setObject(Parser::Nothing());
        } else if (Parser::ReturnStringValueFromJson(doc, "toDo") == "nothing"){
            toReturn.setObject(Parser::Nothing());
        } else if(Parser::ReturnStringValueFromJson(doc, "toDo") == "asking") {
            std::cout<<Parser::ReturnStringValueFromJson(doc, "name")<<std::endl;
            std::string value = Memory::get_instance()->getInUse().returnValue(Parser::ReturnStringValueFromJson(doc, "name"), Memory::get_instance()->getInUse().GetHead());
            toReturn.setObject(Parser::CreateJsonObj_Value(value));
            //std::cout<<"VALOR: " + value<<std::endl;
        }
        std::cout<<Parser::ReturnChar(toReturn).c_str()<<std::endl;
        send(clientSockect, Parser::ReturnChar(toReturn).c_str(), Parser::ReturnChar(toReturn).size() + 1, 0);
    }
    close(clientSockect);

}
