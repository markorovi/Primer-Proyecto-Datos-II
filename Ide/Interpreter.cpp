//
// Created by joel on 19/4/21.
//
#include "../Sockets/Parser.h"
#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "Interpreter.h"


Interpreter::Interpreter() {

    keyWords.append("int");
    keyWords.append("long");
    keyWords.append("char");
    keyWords.append("float");
    keyWords.append("double");
    keyWords.append("struct");
    keyWords.append("reference");

    operators.append("+");
    operators.append("-");
    operators.append("*");
    operators.append("/");
    operators.append("equals");
    operators.append("getAddr");
    operators.append("getValue");


}

Interpreter::Interpreter(QPlainTextEdit *terminalOutput, QPlainTextEdit *_appLog) {
    terminal = terminalOutput;
    appLog = _appLog;

    keyWords.append("int");
    keyWords.append("long");
    keyWords.append("char");
    keyWords.append("float");
    keyWords.append("double");
    keyWords.append("struct");
    keyWords.append("reference");

    operators.append("+");
    operators.append("-");
    operators.append("*");
    operators.append("/");
    operators.append("equals");
    operators.append("getAddr");
    operators.append("getValue");


}

Interpreter::~Interpreter() {

}

void Interpreter::readCode(QString code) {

    QStringList lines = code.split("\n");
    lines.removeAll("");


    for (int i = 0; i < lines.size(); i++) {
        words.append(lines[i].split(" "));
        words[i].removeAll("");
    }


    for (int i = 0; i < words.size() - 1; i++) {
        for (int j = 0; j < words[i].size(); j++) {
            if (words[i][j].contains("\"") && words[i][j].count("\"") == 1) {

                words[i][j] = words[i][j] + " " + words[i][j + 1];
                //words[i].remove(j + 1);
                words[i].removeAt(j + 1);
                j--;
            }

            if (j == words[i].size() - 1 && words[i][j].contains(";")) {
                words[i][j].remove(";");
                words[i].append("-endl");
            }
        }
    }

    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j < words[i].size(); j++) {
            if (words[i][j].contains("reference")) {

                QStringList aux = words[i][j].split("<");
                words[i][j] = aux[0];
                words[i].insert(j + 1, "<");
                aux = aux[1].split(">");
                words[i].insert(j + 2, aux[0]);
                words[i].insert(j + 3, ">");

            } else if (words[i][j].contains("print") || words[i][j].contains("printf") ||
                       words[i][j].contains("getAddr") || words[i][j].contains("getValue")) {

                QStringList aux = words[i][j].split("(");
                words[i][j] = aux[0];
                words[i].insert(j + 1, "(");
                aux = aux[1].split(")");
                words[i].insert(j + 2, aux[0]);
                words[i].insert(j + 3, ")");

            } else if (words[i][j].contains(".")) {

                QStringList aux = words[i][j].split(".");
                words[i][j] = aux[0];
                words[i].insert(j + 1, "dot");
                words[i].insert(j + 2, aux[1]);
            } else if (words[i][j].contains("=")) {

                words[i][j].replace("=", "equals");
            }
        }
    }

    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j < words[i].size(); j++) {
            if (words[i][j].contains("\t")) {
                words[i][j].replace("\t", "");
            }
        }
    }


    for (int i = 0; i < words.size(); i++) {
        for (int j = 1; j < words[i].size() - 1; j++) {
            if (words[i][j] == "dot") {

                words[i][j - 1] = words[i][j - 1] + "." + words[i][j + 1];

                words[i].removeAt(j + 1);
                words[i].removeAt(j);

                j--;
                j--;
            }
        }
    }
    int lastAux = words.size() - 1;

    words.last()[words.last().size() - 1].remove(";");
    words.last().append("-endl");


    qDebug() << "\n\n";
    showCode();
    qDebug() << "\n\n";

}

QList<QStringList> Interpreter::getWords() {
    return words;
}

QString Interpreter::whatIs(QString word) {
    QString strAux;

    if (keyWords.contains(word)) {
        strAux = "keyWord";

    } else if (operators.contains(word)) {
        strAux = "operator";

    } else if (word == "{") {
        strAux = "startScope";

    } else if (word == "}") {
        strAux = "endScope";

    } else if (word == "cout" || word == "print" || word == "printf") {
        strAux = "stdKey";

    } else if (word == "(" || word == "<<") {
        strAux = "bracketStart";

    } else if (word == ")") {
        strAux = "bracketFinal";

    } else if (word == "-endl") {
        strAux = "end";

    } else if (word == "dot") {
        strAux = "accessTo";

    } else if (word == "->") {
        strAux = "error";

    } else {
        strAux = "variable";
    }

    return strAux;
}

void Interpreter::interpretCode(int line) {
    //qDebug()<<words[line]<<"\n";
    QJsonDocument doc;
    freeingScope = false;
    if (line < words.size()) {
        scope = true;
        if (words[line].size() == 1) {
            if (whatIs(words[line][0]) == "startScope") {
                if (inScope) {
                    showInAppLog("Error");
                } else if (inStruct) {
                    showInAppLog("Error");

                } else {
                    inScope = true;
                    scope = false;
                    showInAppLog("Un Scope ha sido abierto");
                    doc.setObject(Parser::Nothing());
                    std::string json = Parser::ReturnChar(doc);
                    MainWindow::setJson(json);
                }

            } else if (whatIs(words[line][0]) == "endScope") {
                if (inScope) {
                    inScope = false;
                    freeingScope = true;
                    showInAppLog("Un Scope ha sido cerrado");
                    doc.setObject(Parser::Nothing());
                    std::string json = Parser::ReturnChar(doc);
                    MainWindow::setJson(json);

                } else if (inStruct) {
                    inStruct = false;

                } else {
                    showInAppLog("Error");
                }

            } else {
                showInAppLog("Error");
            }
        } else if (words[line].size() == 3 && words[line][0] == "struct" && whatIs(words[line][1]) == "variable" &&
                   whatIs(words[line][2]) == "endScope") {

            if (inStruct) {
                showInAppLog("Error: No se permite hacer concatenación de structs");
            } else if (inScope) {
                showInAppLog("Error: No se permite hacer concatenación de structs con scopes");
            } else {
                inStruct = true;
            }


        } else {
            //qDebug()<<"Starting...";
            //qDebug()<<whatIs(words[line][words[line].size()-1]);

            if (whatIs(words[line][words[line].size() - 1]) == "end") {
                //qDebug()<<whatIs(words[line][0]);
                //qDebug()<<words[line][0];
                if (whatIs(words[line][0]) == "keyWord") {
                    //qDebug()<<whatIs(words[line][1]);
                    if (whatIs(words[line][1]) == "variable" /*&& !isExisting(words[line][1])*/) {
                        //qDebug()<<whatIs(words[line][2]);
                        if (whatIs(words[line][2]) == "end") {
                            //qDebug()<<"Declaration without definition";

                            QString type = words[line][0];
                            QString label = words[line][1];
                            QString Value = "null";

                            doc.setObject(Parser::CreateJsonObj_NoAddress(type.toStdString(), label.toStdString(),
                                                                          "")); //Genera el documento con los rasgos de dentro
                            std::string Json = Parser::ReturnChar(
                                    doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                            MainWindow::setJson(Json);
                            qDebug() << type << label << Value;

                            if (inScope) {
                                scopeLabels.append(label);
                            }

                        } else if (whatIs(words[line][2]) == "operator" && words[line][2] == "equals") {
                            //qDebug()<<whatIs(words[line][3]);
                            if (whatIs(words[line][3]) == "variable" /*&& isExisting(words[line][3])*/) {
                                //qDebug()<<"3 caminos: número, char o variable";

                                if (!isNumber(words[line][3]) && !isChar(words[line][3])) {
                                    words[line][3] = getValue(words[line][3]);
                                    //qDebug()<<getValue(words[line][3]);
                                }


                                if (isNumber(words[line][3])) {
                                    //qDebug()<<"Número";

                                    if ((words[line][0] == "int" || words[line][0] == "long" ||
                                         words[line][0] == "float" || words[line][0] == "double")) {
                                        if (whatIs(words[line][4]) == "end") {

                                            QString type = words[line][0];
                                            QString label = words[line][1];
                                            QString Value = words[line][3];

                                            doc.setObject(Parser::CreateJsonObj_NoAddress(type.toStdString(),
                                                                                          label.toStdString(),
                                                                                          Value.toStdString()));
                                            std::string Json = Parser::ReturnChar(
                                                    doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                            MainWindow::setJson(Json);
                                            qDebug() << type << label << Value;

                                            if (inScope) {
                                                scopeLabels.append(label);
                                            } else if (inStruct) {

                                                //structs[0].append(label);
                                            }


                                        } else if (whatIs(words[line][4]) == "operator") {
                                            if (words[line][4] == "+" || words[line][4] == "-" ||
                                                words[line][4] == "*" || words[line][4] == "/") {
                                                if (whatIs(words[line][5]) == "end") {
                                                    showInAppLog("Error");
                                                    //Error
                                                } else if (whatIs(words[line][5]) == "variable") {

                                                    if (whatIs(words[line][6]) == "end") {

                                                        if (!isNumber(words[line][5]) && !isChar(words[line][5])) {
                                                            words[line][5] = getValue(words[line][5]);
                                                        }

                                                        QString type = words[line][0];
                                                        QString label = words[line][1];

                                                        if (isNumber(words[line][5])) {

                                                            if (words[line][4] == "+") {

                                                                if (words[line][0] == "int") {
                                                                    //qDebug()<<"int declarado";

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toInt() +
                                                                             words[line][5].toInt()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "float") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toFloat() +
                                                                             words[line][5].toFloat()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "double") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toDouble() +
                                                                             words[line][5].toDouble()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "long") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toLong() +
                                                                             words[line][5].toLong()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else {
                                                                    qDebug() << "Error";
                                                                }

                                                            } else if (words[line][4] == "-") {
                                                                if (words[line][0] == "int") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toInt() -
                                                                             words[line][5].toInt()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "float") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toFloat() -
                                                                             words[line][5].toFloat()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "double") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toDouble() -
                                                                             words[line][5].toDouble()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "long") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toLong() -
                                                                             words[line][5].toLong()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }
                                                                }
                                                            } else if (words[line][4] == "*") {

                                                                if (words[line][0] == "int") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toInt() *
                                                                             words[line][5].toInt()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "float") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toFloat() *
                                                                             words[line][5].toFloat()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "double") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toDouble() *
                                                                             words[line][5].toDouble()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "long") {

                                                                    QString Value = QString::number(
                                                                            (words[line][3].toLong() *
                                                                             words[line][5].toLong()));
                                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                            type.toStdString(), label.toStdString(),
                                                                            Value.toStdString()));
                                                                    std::string Json = Parser::ReturnChar(
                                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);
                                                                    qDebug() << type << label << Value;

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }
                                                                }
                                                            } else if (words[line][4] == "/") {
                                                                if (words[line][0] == "int") {
                                                                    if (words[line][5].toInt() != 0) {

                                                                        QString Value = QString::number(
                                                                                (words[line][3].toInt() /
                                                                                 words[line][5].toInt()));
                                                                        doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                                type.toStdString(), label.toStdString(),
                                                                                Value.toStdString()));
                                                                        std::string Json = Parser::ReturnChar(
                                                                                doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                        MainWindow::setJson(Json);
                                                                        qDebug() << type << label << Value;

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else if (words[line][0] == "float") {
                                                                    if (words[line][5].toFloat() != 0) {

                                                                        QString Value = QString::number(
                                                                                (words[line][3].toFloat() /
                                                                                 words[line][5].toFloat()));
                                                                        doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                                type.toStdString(), label.toStdString(),
                                                                                Value.toStdString()));
                                                                        std::string Json = Parser::ReturnChar(
                                                                                doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                        MainWindow::setJson(Json);
                                                                        qDebug() << type << label << Value;

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else if (words[line][0] == "double") {
                                                                    if (words[line][5].toDouble() != 0) {

                                                                        QString Value = QString::number(
                                                                                (words[line][3].toDouble() /
                                                                                 words[line][5].toDouble()));
                                                                        doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                                type.toStdString(), label.toStdString(),
                                                                                Value.toStdString()));
                                                                        std::string Json = Parser::ReturnChar(
                                                                                doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                        MainWindow::setJson(Json);
                                                                        qDebug() << type << label << Value;

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else if (words[line][0] == "long") {
                                                                    if (words[line][5].toLong() != 0) {

                                                                        QString Value = QString::number(
                                                                                (words[line][3].toLong() /
                                                                                 words[line][5].toLong()));
                                                                        doc.setObject(Parser::CreateJsonObj_NoAddress(
                                                                                type.toStdString(), label.toStdString(),
                                                                                Value.toStdString()));
                                                                        std::string Json = Parser::ReturnChar(
                                                                                doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                        MainWindow::setJson(Json);
                                                                        qDebug() << type << label << Value;

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else {
                                                                    //Error
                                                                    showInAppLog("Error");
                                                                }

                                                            } else {
                                                                //Error
                                                                showInAppLog("Error");
                                                            }
                                                        }
                                                    } else {
                                                        //Error
                                                        showInAppLog("Error");
                                                    }
                                                } else {
                                                    //Error
                                                    showInAppLog("Error");
                                                }

                                            } else {
                                                showInAppLog("Error");
                                            }
                                        } else {
                                            showInAppLog("Error");
                                        }
                                    } else if (isChar(
                                            words[line][3])) {  ///////////////////////////////////////////////////////////////////////////////
                                        if (words[line][0] == "char") {


                                            //qDebug()<<"Char";
                                            if (whatIs(words[line][4]) == "end") {
                                                QString type = words[line][0];
                                                QString label = words[line][1];
                                                QString Value = words[line][3];
                                                Value.remove("\"");

                                                if (Value.size() == 1) {
                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(type.toStdString(),
                                                                                                  label.toStdString(),
                                                                                                  Value.toStdString()));
                                                    std::string Json = Parser::ReturnChar(
                                                            doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                    MainWindow::setJson(Json);
                                                    qDebug() << type << label << Value;

                                                    if (inScope) {
                                                        scopeLabels.append(label);
                                                    }

                                                } else {
                                                    showInAppLog("Error");
                                                }
                                            } else {
                                                //Error
                                                showInAppLog("Error");
                                            }
                                        } else {
                                            showInAppLog("Error");
                                        }
                                    } else if (words[line][3].contains("\"")) {
                                        //Error
                                        showInAppLog("Error");

                                    } else { //Variable guardada en memoria
                                        //Buscar variable en memoria
//                                        QString aux = getValue(words[line][3]);
                                        showInAppLog("Error");
//                                        showInAppLog(aux);
                                    }
                                } else {
                                    //Error
                                    showInAppLog("Error");
//                                    QString aux = getValue(words[line][3]);
//                                    showInAppLog(aux);
                                }

                            } else {
                                //Error
                                showInAppLog("Error");
                            }

                        } else {
                            //Error
                            showInAppLog("Error");
                        }

                    } else if (whatIs(words[line][0]) == "variable") {

                        //Buscar si existe y si no, tirar error

                    } else if (whatIs(words[line][0]) == "stdKey") {
                        doc.setObject(Parser::Nothing());
                        std::string Json = Parser::ReturnChar(
                                doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                        MainWindow::setJson(Json);
                        //Printear en la terminal

                    } else {
                        //Error
                        showInAppLog("Error");
                    }

                } else if ((whatIs(words[line][0]) == "stdKey")) {
                    if ((whatIs(words[line][1]) == "bracketStart")) {
                        if (words[line][1] == "<<") {
                            if (whatIs(words[line][2]) == "variable") {
                                if (whatIs(words[line][3]) == "end") {
                                    showInTerminal(words[line][2]);
                                } else {
                                    showInAppLog("Error");
                                }
                            } else {
                                showInAppLog("Error");
                            }
                        } else if (words[line][1] == "(") {

                        }
                    } else {
                        showInAppLog("Error");
                    }
                } else {
                    //Error
                    showInAppLog("Error");
                }
            }
        }
    }

    qDebug() << scopeLabels;
    //qDebug()<< MainWindow::getJson().c_str()<<endl;
//    QJsonDocument doc2 = Parser::ReturnJson(MainWindow::getJson); //Devolver lo que llego por el socket a json
//    std::cout<<Parser::ReturnStringValueFromJson(doc, "name"); //Obtener un valor de json
}

void Interpreter::showCode() {
    for (int i = 0; i < words.size(); i++) {
        qDebug() << words[i];
    }
}

bool Interpreter::isExisting(QString variable) {
    if (variable == "") {
        return true;
    }
    return true;
}

bool Interpreter::isNumber(QString value) {
    bool aux = true;
    bool dotOne = true;

    for (int i = 0; i < value.size(); i++) {
        QString a = ".";
        aux = value[i].isDigit();

        if (value[value.size() - 1] == a[0]) {
            dotOne = false;
            aux = false;
        }

        if (!aux) {
            if (value[i] == a[0] && dotOne) {
                aux = true;
                dotOne = false;

            } else {
                break;
            }
        }
    }

    return aux;
}

bool Interpreter::isChar(QString value) {
    bool aux = value.startsWith("\"") && value.endsWith("\"") && value.count("\"") == 2;
    return aux;
}

void Interpreter::setTerminal(QPlainTextEdit *terminalOutput) {
    terminal = terminalOutput;
}

void Interpreter::setAppLog(QPlainTextEdit *newAppLog) {
    appLog = newAppLog;
}

void Interpreter::showInTerminal(QString msg) {
    terminal->appendPlainText(">> " + msg);
}

void Interpreter::showInAppLog(QString msg) {
    appLog->appendPlainText(">> " + msg);
}

void Interpreter::freeScope() {
    freeingScope = true;
}

bool Interpreter::isScope() const {
    return scope;
}

bool Interpreter::isFreeingScope() const {
    return freeingScope;
}

const QStringList &Interpreter::getScopeLabels() const {
    return scopeLabels;
}

void Interpreter::setFreeingScope(bool freeingScope) {
    Interpreter::freeingScope = freeingScope;
}

void Interpreter::setClient(Client *client) {
    Interpreter::client = client;
}

QString Interpreter::getValue(QString aux) {
    QJsonDocument doc;
    doc.setObject(Parser::CreateJsonObj_Asking(aux.toStdString()));
    std::string json = Parser::ReturnChar(doc);
    MainWindow::setJson(json);
    client->Start();


    qDebug() << "LO QUE IMPORTA, aux = " + aux + " y  el qDebug " +
                QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value"));
    return QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value"));
}

