//
// Created by marco on 4/22/21.
//
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "Parser.h"


QJsonObject Parser::CreateJsonObj_NoAddress(std::string type, std::string name, std::string value){
    QJsonObject obj;
    obj["toDo"] = "assign";
    obj["type"] = type.c_str();
    obj["name"] = name.c_str();
    obj["value"] = value.c_str();
    return obj;
}


QJsonObject Parser::CreateJsonObj_Address(std::string type, std::string name, std::string value, std::string address){
    QJsonObject obj;
    obj["type"] = type.c_str();
    obj["name"] = name.c_str();
    obj["value"] = value.c_str();
    obj["address"] = address.c_str();
    return obj;
}

std::string Parser::ReturnChar(QJsonDocument document){
    QString strJson(document.toJson(QJsonDocument::Compact)); //QJsonDocument to QString
    std::string str =  strJson.toUtf8().constData(); //QString to string
    return str; //String to char (to be able to send it through sockets)
}

std::string Parser::ReturnStringValueFromJson(QJsonDocument document, std::string value) {
    return document.object().value(QString(value.c_str())).toString().toUtf8().constData();
}
QJsonDocument Parser::ReturnJson(const char* inbox){
    std::string str = static_cast<std::string>(inbox); //Char to string
    QString Qstr = QString::fromUtf8(str.c_str()); //String to QString
    QJsonDocument document = QJsonDocument::fromJson(Qstr.toUtf8()); //QString to QJsonDocument
//    std::cout<<Parser::ReturnStringValueFromJson(document, "name");
//    std::cout<<"teset"<<std::endl;
    return document;
}
