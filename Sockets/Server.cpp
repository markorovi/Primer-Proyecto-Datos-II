//
// Created by marco on 4/20/21.
//
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <sstream>
#include "../Memory/Memory.h"
#include "Server.h"
#include <string>
#include <iostream>


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
            std::string value = Memory::get_instance()->getInUse().returnValue(Parser::ReturnStringValueFromJson(doc, "name"), Memory::get_instance()->getInUse().GetHead());
            toReturn.setObject(Parser::CreateJsonObj_ReturnsData(value));
            //std::cout<<"VALOR: " + value<<std::endl;



//        } else if (Parser::ReturnStringValueFromJson(doc, "atoDo") == "whatType"){
//            std::string type = Memory::get_instance()->getInUse().returnType(Parser::ReturnStringValueFromJson(doc, "name"), Memory::get_instance()->getInUse().GetHead());
//            toReturn.setObject(Parser::CreateJsonObj_ReturnsData(type));
//
//        } else if (Parser::ReturnStringValueFromJson(doc, "atoDo") == "newStruct"){
//            int num;
//            int size;
//            num = std::stoi(Parser::ReturnStringValueFromJson(doc, "integers"));
//            while (num != 0){
//                size += 4;
//                num--;
//            }
//            num = std::stoi(Parser::ReturnStringValueFromJson(doc, "longs"));
//            while (num != 0){
//                size += 8;
//                num--;
//            }
//            num = std::stoi(Parser::ReturnStringValueFromJson(doc, "doubles"));
//            while (num != 0){
//                size += 8;
//                num--;
//            }
//            num = std::stoi(Parser::ReturnStringValueFromJson(doc, "chars"));
//            while (num != 0){
//                size += 1;
//                num--;
//            }
//            num = std::stoi(Parser::ReturnStringValueFromJson(doc, "floats"));
//            while (num != 0){
//                size += 4;
//                num--;
//            }
//            Memory::get_instance()->GeneratingStruct(size, Parser::ReturnStringValueFromJson(doc, "name"));
//            void *address = Memory::get_instance()->getInUse().GetHead()->GetAddress();
//            std::stringstream ss;
//            ss << address;
//            std::string strAddress = ss.str();
//            toReturn.setObject(Parser::CreateJsonObj_Address("struct", Parser::ReturnStringValueFromJson(doc, "name"), "", strAddress));
//
//            //std::cout<<"El tamaño es: "<<size<<std::endl;
//
//
//        } else if (Parser::ReturnStringValueFromJson(doc, "atoDo") == "fillStruct"){ //hay que quitar lo que hace que devuelva la direccion, porque esto no se ve en la ram view//////////////////////////////
//
//            Memory::get_instance()->FillingStruct(Parser::ReturnStringValueFromJson(doc, "type"), "", Parser::ReturnStringValueFromJson(doc, "name") + "_struct");
//            void *address = Memory::get_instance()->getInUse().GetHead()->GetAddress();
//            std::stringstream ss;
//            ss << address;
//            std::string strAddress = ss.str();
//            toReturn.setObject(Parser::CreateJsonObj_Address("struct", Parser::ReturnStringValueFromJson(doc, "name"), "", strAddress));
//
//            std::cout<<"Dirección: "<<Memory::get_instance()->getInUse().GetHead()->GetAddress()<<std::endl;
//            toReturn.setObject(Parser::Nothing());
//        } else if (Parser::ReturnStringValueFromJson(doc, "atoDo") == "modifyStruct") {
//            Node* iterator = Memory::get_instance()->getInUse().GetHead();
//            while (iterator->GetName() != Parser::ReturnStringValueFromJson(doc, "toModify")){
//                iterator = iterator->GetNext();
//            }
//            iterator = iterator->GetNext();
//            while (iterator->GetName() != Parser::ReturnStringValueFromJson(doc, "name")){
//                iterator = iterator->GetNext();
//            }
//            Memory::get_instance()->Rewrite(iterator->GetAddress(), Parser::ReturnStringValueFromJson(doc, "type"), Parser::ReturnStringValueFromJson(doc, "value"));
//            toReturn.setObject(Parser::Nothing());
//
//        } else if (Parser::ReturnStringValueFromJson(doc, "atodo") == "isAttribute"){
//            std::string flag = "false";
//            std::cout<<"Está entrando a la pregunta";
//            Node* iterator = Memory::get_instance()->getInUse().GetHead();
//            while (iterator->GetName() != Parser::ReturnStringValueFromJson(doc, "name")){
//                iterator = iterator->GetNext();
//            }
//            int size = iterator->GetSize();
//            std::cout<<"Encuentra el struct";
//            while (size > 0) {
//                if (iterator->GetType() == "int") {
//                    iterator = iterator->GetNext();
//                    size=-4;
//                    if (iterator->GetName() == Parser::ReturnStringValueFromJson(doc, "attribute")+"_struct"){
//                        flag = "true";
//                    }
//                } else if (iterator->GetType() == "char") {
//                    iterator = iterator->GetNext();
//                    size=-1;
//                    if (iterator->GetName() == Parser::ReturnStringValueFromJson(doc, "attribute")+"_struct"){
//                        flag = "true";
//                    }
//                } else if (iterator->GetType() == "long") {
//                    iterator = iterator->GetNext();
//                    size=-8;
//                    if (iterator->GetName() == Parser::ReturnStringValueFromJson(doc, "attribute")+"_struct"){
//                        flag = "true";
//                    }
//                } else if (iterator->GetType() == "double") {
//                    iterator = iterator->GetNext();
//                    size=-8;
//                    if (iterator->GetName() == Parser::ReturnStringValueFromJson(doc, "attribute")+"_struct"){
//                        flag = "true";
//                    }
//                } else if (iterator->GetType() == "float") {
//                    iterator = iterator->GetNext();
//                    size=-4;
//                    if (iterator->GetName() == Parser::ReturnStringValueFromJson(doc, "attribute")+"_struct"){
//                        flag = "true";
//                    }
//                }
//            }
//            std::cout<<"Responde el mensaje";
//            toReturn.setObject(Parser::CreateJsonObj_ReturnsData(flag));
//        toReturn.setObject(Parser::Nothing());
        }
        std::cout<<Parser::ReturnChar(toReturn).c_str()<<std::endl;
        send(clientSockect, Parser::ReturnChar(toReturn).c_str(), Parser::ReturnChar(toReturn).size() + 1, 0);
    }
    close(clientSockect);

}
