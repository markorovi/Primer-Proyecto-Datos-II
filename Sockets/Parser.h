//
// Created by marco on 4/22/21.
//

#include "QApplication"
#include <iostream>
#ifndef IDE_PARSER_H
#define IDE_PARSER_H


class Parser {
public:
static std::string ReturnChar(QJsonDocument document);
static std::string ReturnStringValueFromJson(QJsonDocument document, std::string value);
static QJsonDocument ReturnJson(const char* inbox);
static QJsonDocument ReturnJsonFromStr(std::string text);
static QJsonObject CreateJsonObj_Free(std::string name);
static QJsonObject CreateJsonObj_NoAddress(std::string type, std::string name, std::string value);
static QJsonObject CreateJsonObj_Address(std::string type, std::string name, std::string value, std::string address);
static QJsonObject CreateJsonObj_Asking(std::string name);
static QJsonObject CreateJsonObj_Value(std::string name);
static QJsonObject Nothing();
};


#endif //IDE_PARSER_H
