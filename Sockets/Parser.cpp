//
// Created by marco on 4/22/21.
//
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "Parser.h"

/// Se encarga de generar un QJsonDocument el cual sera utilizado para cuando se desear agregar variables a memoria
/// \param type std::string El tipo de la variable
/// \param name std::string El nombre de la vairable
/// \param value std::string El valor que la variable almacenara
/// \return QJsonObject
QJsonObject Parser::CreateJsonObj_NoAddress(std::string type, std::string name, std::string value){
    QJsonObject obj;
    obj["toDo"] = "assign";
    obj["type"] = type.c_str();
    obj["name"] = name.c_str();
    obj["value"] = value.c_str();
    return obj;
}

QJsonObject Parser::CreateJsonObj_Free(std::string name){
    QJsonObject obj;
    obj["toDo"] = "free";
    obj["name"] = name.c_str();
    return obj;
}

QJsonObject Parser::CreateJsonObj_Asking(std::string name){
    QJsonObject obj;
    obj["toDo"] = "asking";
    obj["name"] = name.c_str();
    return obj;
}

/// Se encarga de generar un QJsonDocument el cual sera utilizado como un simple mensaje vacio que sera enviado al servidor cuando este no debe de realizar nada
/// \return QJsonObject
QJsonObject Parser::Nothing(){
    QJsonObject obj;
    obj["toDo"] = "nothing";
    return obj;
}


QJsonObject Parser::CreateJsonObj_Value(std::string name) {
    QJsonObject obj;
    obj["value"] = name.c_str();
    return obj;
}


/// Se encarga de generar un QJsonDocument el cual sera utilizado para cuando se reenviara al cliente el como la variable que se deseaba guardar se guardo
/// \param type std::string El tipo de la variable
/// \param name std::string El nombre de la vairable
/// \param value std::string El valor que la variable almacenara
/// \param address std::string La direccion de memoria
/// \return QJsonObject
QJsonObject Parser::CreateJsonObj_Address(std::string type, std::string name, std::string value, std::string address){
    QJsonObject obj;
    obj["type"] = type.c_str();
    obj["name"] = name.c_str();
    obj["value"] = value.c_str();
    obj["address"] = address.c_str();
    return obj;
}

/// Se encarga de convertir un QJsonDocument a un std::string
/// \param document QJsonDocument Documento a parsear
/// \return std::string
std::string Parser::ReturnChar(QJsonDocument document){
    QString strJson(document.toJson(QJsonDocument::Compact)); //QJsonDocument to QString
    std::string str =  strJson.toUtf8().constData(); //QString to string
    return str; //String to char (to be able to send it through sockets)
}

/// Se encarga de obtener un valor especifico de un QJsonDocument
/// \param document QJsonDocument Documento sobre el cual trabajar
/// \param value std::string Valor que se desea obtener
/// \return std::string
std::string Parser::ReturnStringValueFromJson(QJsonDocument document, std::string value) {
    return document.object().value(QString(value.c_str())).toString().toUtf8().constData();
}

/// Se encarga de convertir un conjuto de chars en el QJsonDocumt
/// \param inbox Caracteres a parsear
/// \return QJsonDocument
QJsonDocument Parser::ReturnJson(const char* inbox){
    std::string str = static_cast<std::string>(inbox); //Char to string
    QString Qstr = QString::fromUtf8(str.c_str()); //String to QString
    QJsonDocument document = QJsonDocument::fromJson(Qstr.toUtf8()); //QString to QJsonDocument
    return document;
}

/// Se encarga de convertir un std::string a un QJsonDocument
/// \param text std::string Valor a parsear
/// \return QJsonDocument
QJsonDocument Parser::ReturnJsonFromStr(std::string text){
    QString Qstr = QString::fromUtf8(text.c_str()); //String to QString
    QJsonDocument document = QJsonDocument::fromJson(Qstr.toUtf8()); //QString to QJsonDocument
    return document;
}