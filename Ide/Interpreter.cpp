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
    if(inStruct){
        qDebug()<<"El valor de inStruct es: Verdadero";

    } else{
        qDebug()<<"El valor de inStruct es: Falso";

    }
    //qDebug()<<words[line];
    for(int i=0; i<words[line].size(); i++){
        //qDebug()<<whatIs(words[line][i]);
    }

    freeingScope = false;
    if (line < words.size()) {
        scope = true;
        if (words[line].size() == 1) {
            if (whatIs(words[line][0]) == "startScope") {
                if (inScope) {
                    showInAppLog("Error: No se puede concatenar scopes");
                } else if (inStruct) {
                    showInAppLog("Error: No se pueden concatenar scopes");

                } else {
                    inScope = true;
                    scope = false;
                    showInAppLog("Un Scope ha sido abierto");
                    doc.setObject(Parser::Nothing());
                    std::string json = Parser::ReturnChar(doc);
                    MainWindow::setJson(json);
                }

            } else if (whatIs(words[line][0]) == "endScope") {

                doc.setObject(Parser::Nothing()); //Genera el documento con los rasgos de dentro
                std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                MainWindow::setJson(Json);

                if (inScope) {
                    inScope = false;
                    freeingScope = true;
                    showInAppLog("Un Scope ha sido cerrado");
                    doc.setObject(Parser::Nothing());
                    std::string json = Parser::ReturnChar(doc);
                    MainWindow::setJson(json);

                } else if (inStruct) {
                    inStruct = false;
                    qDebug()<<"Dentro del struct hay:";
                    structList.append(structs);
                    structs.clear();
                    for(int i = 0; i<structList.size(); i++){

                        qDebug()<<"";

                        for (int j = 0; j < structList[i].size(); ++j) {
                            qDebug()<<structList[i][j];
                        }
                    }



                } else {
                    showInAppLog("Error: no se puede cerrar el Struct o el scope si no se ha iniciado uno previamente");
                }

            } else {
                showInAppLog("Error: par??metros incorrectos");
            }
        } else if (words[line].size() == 3 && words[line][0] == "struct" && whatIs(words[line][1]) == "variable" && whatIs(words[line][2]) == "startScope") {
            qDebug()<<"Se encuentra declarando un struct";
            if (inStruct) {
                showInAppLog("Error: No se permite hacer concatenaci??n de structs");
            } else if (inScope) {
                showInAppLog("Error: No se permite hacer concatenaci??n de structs con scopes");
            } else {
                inStruct = true;
                auxStructs.append(words[line][1]);
                structs.append(auxStructs);
                auxStructs.clear();
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


                            if(inStruct){
                                auxStructs.append(type);
                                auxStructs.append(label);
                                auxStructs.append(Value);
                                structs.append(auxStructs);
                                auxStructs.clear();


                                doc.setObject(Parser::Nothing()); //Genera el documento con los rasgos de dentro
                                std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                MainWindow::setJson(Json);

                            } else {

                                doc.setObject(Parser::CreateJsonObj_NoAddress(type.toStdString(), label.toStdString(),"")); //Genera el documento con los rasgos de dentro
                                std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                MainWindow::setJson(Json);
                                qDebug() << type << label << Value;

                                if (inScope) {
                                    scopeLabels.append(label);
                                }
                            }

                        } else if (whatIs(words[line][2]) == "operator" && words[line][2] == "equals") {
                            //qDebug()<<whatIs(words[line][3]);
                            if (whatIs(words[line][3]) == "variable" /*&& isExisting(words[line][3])*/) {
                                //qDebug()<<"3 caminos: n??mero, char o variable";

                                if (!isNumber(words[line][3]) && !isChar(words[line][3])) {
                                    words[line][3] = getValue(words[line][3]);
                                    //qDebug()<<getValue(words[line][3]);
                                }


                                if (isNumber(words[line][3])) {
                                    //qDebug()<<"N??mero";

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
                                                qDebug()<<"Dentro del struct est??: ";
                                                for(int i=0; i<structs.size();i++){
                                                    qDebug()<<structs[i];
                                                }
                                                //structs[0].append(label);
                                            }


                                        } else if (whatIs(words[line][4]) == "operator") {
                                            if (words[line][4] == "+" || words[line][4] == "-" || words[line][4] == "*" || words[line][4] == "/") {
                                                if (whatIs(words[line][5]) == "end") {
                                                    showInAppLog("Error: No se ha declarado correctamente la operaci??n");

                                                } else if (whatIs(words[line][5]) == "variable") {
                                                    if (whatIs(words[line][6]) == "end") {

                                                        if (!isNumber(words[line][5]) && !isChar(words[line][5])) {
                                                            words[line][5] = getValue(words[line][5]);
                                                        }

                                                        QString type = words[line][0];
                                                        QString label = words[line][1];
                                                        QString Value;
                                                        if (isNumber(words[line][5])) {

                                                            if (words[line][4] == "+") {

                                                                if (words[line][0] == "int") {
                                                                    //qDebug()<<"int declarado";

                                                                    Value = QString::number((words[line][3].toInt() + words[line][5].toInt()));


                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "float") {

                                                                    QString Value = QString::number((words[line][3].toFloat() + words[line][5].toFloat()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "double") {

                                                                    QString Value = QString::number((words[line][3].toDouble() + words[line][5].toDouble()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "long") {

                                                                    QString Value = QString::number((words[line][3].toLong() + words[line][5].toLong()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else {
                                                                    qDebug() << "Error";
                                                                }

                                                            } else if (words[line][4] == "-") {
                                                                if (words[line][0] == "int") {

                                                                    QString Value = QString::number((words[line][3].toInt() - words[line][5].toInt()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "float") {

                                                                    QString Value = QString::number((words[line][3].toFloat() - words[line][5].toFloat()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "double") {

                                                                    QString Value = QString::number((words[line][3].toDouble() - words[line][5].toDouble()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "long") {

                                                                    QString Value = QString::number((words[line][3].toLong() - words[line][5].toLong()));
                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }
                                                                }
                                                            } else if (words[line][4] == "*") {

                                                                if (words[line][0] == "int") {

                                                                    QString Value = QString::number((words[line][3].toInt() * words[line][5].toInt()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "float") {

                                                                    QString Value = QString::number((words[line][3].toFloat() *words[line][5].toFloat()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "double") {

                                                                    QString Value = QString::number((words[line][3].toDouble() *words[line][5].toDouble()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }

                                                                } else if (words[line][0] == "long") {

                                                                    QString Value = QString::number((words[line][3].toLong() * words[line][5].toLong()));

                                                                    if (inScope) {
                                                                        scopeLabels.append(label);
                                                                    }
                                                                }
                                                            } else if (words[line][4] == "/") {
                                                                if (words[line][0] == "int") {
                                                                    if (words[line][5].toInt() != 0) {

                                                                        QString Value = QString::number((words[line][3].toInt() /words[line][5].toInt()));

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else if (words[line][0] == "float") {
                                                                    if (words[line][5].toFloat() != 0) {

                                                                        QString Value = QString::number((words[line][3].toFloat() /words[line][5].toFloat()));

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else if (words[line][0] == "double") {
                                                                    if (words[line][5].toDouble() != 0) {

                                                                        QString Value = QString::number((words[line][3].toDouble() /words[line][5].toDouble()));

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    }
                                                                } else if (words[line][0] == "long") {
                                                                    if (words[line][5].toLong() != 0) {

                                                                        QString Value = QString::number((words[line][3].toLong() / words[line][5].toLong()));

                                                                        if (inScope) {
                                                                            scopeLabels.append(label);
                                                                        }
                                                                    } else {
                                                                        showInAppLog("Error: no se puede dividir entre 0");
                                                                    }
                                                                } else {
                                                                    //Error
                                                                    showInAppLog("Error: tipo de variable incorrecto");
                                                                }

                                                            } else {
                                                                //Error
                                                                showInAppLog("Error: Operador incorrecto");
                                                            }

                                                            if(Value!=NULL){
                                                                if (!inStruct){
                                                                    toDeclarate(type,label,Value);
                                                                } else {
                                                                    doc.setObject(Parser::Nothing()); //Genera el documento con los rasgos de dentro
                                                                    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                                    MainWindow::setJson(Json);

                                                                    auxStructs.append(type);
                                                                    auxStructs.append(label);
                                                                    auxStructs.append(Value);
                                                                    structs.append(auxStructs);
                                                                    auxStructs.clear();
                                                                }
                                                            }

                                                        } else {
                                                            showInAppLog("Se ha ingrsado un valor incorrecto");
                                                        }
                                                    } else {
                                                        //Error
                                                        showInAppLog("Error: Se debe terminar la l??nea con ;");
                                                    }
                                                } else {
                                                    //Error
                                                    showInAppLog("Error: Se ha digitado una variable incorrecta");
                                                }

                                            } else {
                                                showInAppLog("Error: no se puede realizar esta operaci??n");
                                            }
                                        } else {
                                            showInAppLog("Error: se ha digitado algo incorrecto");
                                        }
                                    } else if (isChar(words[line][3])) {
                                        if (words[line][0] == "char") {


                                            //qDebug()<<"Char";
                                            if (whatIs(words[line][4]) == "end") {
                                                QString type = words[line][0];
                                                QString label = words[line][1];
                                                QString Value = words[line][3];
                                                Value.remove("\"");

                                                if (Value.size() == 1) {
                                                    doc.setObject(Parser::CreateJsonObj_NoAddress(type.toStdString(),label.toStdString(), Value.toStdString()));
                                                    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                                                    MainWindow::setJson(Json);
                                                    qDebug() << type << label << Value;

                                                    if (inScope) {
                                                        scopeLabels.append(label);
                                                    }

                                                } else {
                                                    showInAppLog("Error: no ha ingresado un char");
                                                }
                                            } else {
                                                //Error
                                                showInAppLog("Error: Se debe terminar la l??nea con ;");
                                            }
                                        } else {
                                            showInAppLog("Error: no existe ese tipo de variable");
                                        }
                                    } else if (words[line][3].contains("\"")) {
                                        showInAppLog("Error: se ha digitado algo incorrecto");

                                    } else { //Variable guardada en memoria
                                        //Buscar variable en memoria
//                                        QString aux = getValue(words[line][3]);
                                        showInAppLog("Error: se ha producido un error");
//                                        showInAppLog(aux);
                                    }
                                } else if(isChar(words[line][3])){

                                    if(whatIs(words[line][4])=="end"){
                                        //qDebug()<<"hola";
                                        words[line][3].remove("\"");

                                        QString type = words[line][0];
                                        QString label = words[line][1];
                                        QString Value = words[line][3];

                                        if(Value.size()<2){
                                            toDeclarate(type, label, Value);

                                        } else {
                                            showInAppLog("Error: No se ha ingresado un char");
                                        }
                                    } else {
                                        showInAppLog("Error: Se debe terminar la l??nea con ;");
                                    }

                                } else {
                                    //Error
                                    showInAppLog("Error: No se reconoce la variable");
//                                    QString aux = getValue(words[line][3]);
//                                    showInAppLog(aux);
                                }

                            } else {
                                //Error
                                showInAppLog("Error: No se reconoce la variable");
                            }

                        } else {
                            //Error
                            showInAppLog("Error: se ha digitado un operador incorrecto");
                        }

                    } else if (whatIs(words[line][0]) == "variable") {

                        //Buscar si existe y si no, tirar error

                    } else if (whatIs(words[line][0]) == "stdKey") {
                        doc.setObject(Parser::Nothing());
                        std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                        MainWindow::setJson(Json);
                        //Printear en la terminal

                    } else {
                        //Error
                        showInAppLog("Error: se ha digitado algo incorrecto");
                    }

                } else if ((whatIs(words[line][0]) == "stdKey")) {
                    doc.setObject(Parser::Nothing());
                    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
                    MainWindow::setJson(Json);

                    if ((whatIs(words[line][1]) == "bracketStart")) {
                        if (words[line][1] == "<<") {
                            if (whatIs(words[line][2]) == "variable") {
                                if (whatIs(words[line][3]) == "end") {

                                    if(!isNumber(words[line][2])&&!isChar(words[line][2])){
                                        words[line][2]=getValue(words[line][2]);
                                    }

                                    showInTerminal(words[line][2]);

                                } else {
                                    showInAppLog("Error: Se debe terminar la l??nea con ;");
                                }
                            } else {
                                showInAppLog("Error: No se reconoce la variable");
                            }
                        } else if (words[line][1] == "(") {

                        }
                    } else {
                        showInAppLog("Error: no se puede utilizar el cout");
                    }
                } else if(isStruct(words[line][0])){
                    if(whatIs(words[line][1])=="variable"){
                        if(whatIs(words[line][2])=="end"){

                            int integers = 0, doubles = 0, longs = 0, floats = 0, chars = 0;

                            for(int i = 0; i<structList.size(); i++) {
                                if(words[line][0]==structList[i][0][0]){
                                    for (int j = 0; j < structList[i].size(); j++) {

                                        integers += structList[i][j].count("int");
                                        doubles += structList[i][j].count("double");
                                        longs += structList[i][j].count("long");
                                        floats += structList[i][j].count("float");
                                        chars += structList[i][j].count("char");

                                    }

                                    doc.setObject(Parser::CreateJsonObj_NewStructObject(words[line][1].toStdString(), std::to_string(integers),std::to_string(doubles),std::to_string(longs),std::to_string(floats),std::to_string(chars)));
                                    std::string json = Parser::ReturnChar(doc);
                                    MainWindow::setJson(json);
                                    client->Start();
                                    usleep(10000);

                                    for (int j = 1; j<structList[i].size(); j++){

                                        qDebug()<<"Tipo de dato: "<<structList[i][j][0];
                                        qDebug()<<"Struct al que pertenece "<<structList[i][0][0];
                                        qDebug()<<"Nombre del atributo: "<<structList[i][j][1];

                                        doc.setObject(Parser::CreateJsonObj_FillStruct(structList[i][j][0].toStdString(), structList[i][0][0].toStdString(), structList[i][j][1].toStdString()));
                                        std::string json = Parser::ReturnChar(doc);
                                        MainWindow::setJson(json);
                                        client->Start();
                                        usleep(10000);
                                    }
                                }
                            }

                            qDebug()<<"Cantidad de ints:"<<integers;
                            qDebug()<<"Cantidad de doubles:"<<doubles;
                            qDebug()<<"Cantidad de longs:"<<longs;
                            qDebug()<<"Cantidad de floats:"<<floats;
                            qDebug()<<"Cantidad de char:"<<chars;


                        } else {
                            showInAppLog("Error: Se debe terminar la l??nea con ;");
                        }
                    } else {
                        showInAppLog("Error: No se reconoce la variable");
                    }
                } else if(askFor(words[line][0])=="struct"){
                    qDebug()<<"S?? es un struct";
                    qDebug()<<words[line][1];
                    if(whatIs(words[line][1])=="accessTo"){
                        qDebug()<<"IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII";
                        qDebug()<<isAttribute(words[line][0], words[line][2]);
                        qDebug()<<"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
                        if(isAttribute(words[line][0], words[line][2])=="true"){
                            qDebug()<<"S?? es un atributo";
                            if(whatIs(words[line][3])=="equals"){
                                qDebug()<<"S?? es un igual";
                                if(whatIs(words[line][4])=="variable"){
                                    qDebug()<<"S?? es una variable";
                                    if(whatIs(words[line][5])=="end"){

                                        if(!isNumber(words[line][4])&&!isChar(words[line][4])) {
                                            getValue(words[line][4]);
                                        }

                                        qDebug()<<"Entrada final";

                                    } else {
                                        showInAppLog("Error: No fue posible realizar la instruccion");

                                    }
                                } else {
                                    showInAppLog("Error: No fue posible realizar la instruccion");

                                }
                            } else {
                                showInAppLog("Error: No fue posible realizar la instruccion");

                            }
                        } else {
                            showInAppLog("Error: No fue posible realizar la instruccion");
                        }
                    } else {
                        showInAppLog("Error: No fue posible realizar la instruccion");
                    }
                } else {
                    //Error
                    showInAppLog("Error: No fue posible realizar la instruccion");
                }
            } else{
                showInAppLog("Error: Se debe terminar la l??nea con ;");
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
    bool aux = false;

    if(value[0]=="\"" && value[2]=="\"" && value.size()==3){
        qDebug()<<value;
        aux = true;

    } else if(value.startsWith("\"") && value.endsWith("\"") && value.count("\"")==2 && value.size()>3){
        aux=true;
    }
    aux = value.startsWith("\"")&&value.endsWith("\"")&&value.count("\"")<3;
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

    if(msg.contains("Error")) {
        setStopProgram(true);
    }
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

void Interpreter::toDeclarate(QString type, QString label, QString Value){
    QJsonDocument doc;
    doc.setObject(Parser::CreateJsonObj_NoAddress(type.toStdString(), label.toStdString(), Value.toStdString()));
    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
    MainWindow::setJson(Json);
    qDebug() << type << label << Value;
}

bool Interpreter::isStruct(QString aux) {

    for (int i = 0; i < structList.size(); ++i) {
        if(structList[i][0][0]==aux){
            return true;
        }
    }

    return false;
}

QString Interpreter::askFor(QString aux) {
    QJsonDocument doc;
    doc.setObject(Parser::CreateJsonObj_whatType(aux.toStdString()));
    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
    MainWindow::setJson(Json);
    client->Start();
    usleep(10000);
    return QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value"));
}

QString Interpreter::isAttribute(QString name, QString attribute) {
    QJsonDocument doc;
    doc.setObject(Parser::CreateJsonObj_isAttribute(name.toStdString(),attribute.toStdString()));
    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
    MainWindow::setJson(Json);
    qDebug()<<QString::fromStdString(Parser::ReturnStringValueFromJson(doc,"toDo"));;
    client->Start();
    //usleep(10000);

//    qDebug()<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//    if(QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value"))=="true"){
//        aux= true;
//    } else {
//        aux= false;
//    }
    return QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value"));
}

void Interpreter::setStopProgram(bool stopProgram) {
    Interpreter::stopProgram = stopProgram;
}

bool Interpreter::isStopProgram() const {
    return stopProgram;
}



