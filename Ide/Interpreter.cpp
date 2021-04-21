//
// Created by joel on 19/4/21.
//

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

Interpreter::~Interpreter(){

}

void Interpreter::readCode(QString code){

    QStringList lines = code.split("\n");
    lines.removeAll("");




    for(int i=0; i<lines.size(); i++){
        words.append(lines[i].split(" "));
        words[i].removeAll("");
    }


   for (int i=0; i<words.size(); i++){
        for(int j=0; j<words[i].size(); j++){
            if(words[i][j].contains("\"") && words[i][j].count("\"")==1){

                words[i][j] = words[i][j] + " " + words[i][j+1];
                words[i].remove(j+1);
                j--;
            }

            if (j==words[i].size()-1 && words[i][j].contains(";")){
                words[i][j].remove(";");
                words[i].append("-endl");
            }
        }
   }

   for(int i = 0; i<words.size(); i++){
       for(int j = 0; j<words[i].size(); j++){
           if(words[i][j].contains("reference")){

               QStringList aux = words[i][j].split("<");
               words[i][j]=aux[0];
               words[i].insert(j+1, "<");
               aux = aux[1].split(">");
               words[i].insert(j+2, aux[0]);
               words[i].insert(j+3, ">");

           } else if(words[i][j].contains("print") || words[i][j].contains("printf") || words[i][j].contains("getAddr") || words[i][j].contains("getValue")){

               QStringList aux = words[i][j].split("(");
               words[i][j]=aux[0];
               words[i].insert(j+1, "(");
               aux = aux[1].split(")");
               words[i].insert(j+2, aux[0]);
               words[i].insert(j+3, ")");

           } else if(words[i][j].contains(".")){

               QStringList aux = words[i][j].split(".");
               words[i][j]=aux[0];
               words[i].insert(j+1, "dot");
               words[i].insert(j+2, aux[1]);
           } else if(words[i][j].contains("=")){

               words[i][j].replace("=", "equals");
           }
       }
   }

   for (int i =0; i<words.size(); i++){
       for(int j=0; j<words[i].size(); j++){
           if(words[i][j].contains("\t")){
               words[i][j].replace("\t", "");
           }
       }
   }
}

QList<QStringList> Interpreter::getWords(){
    return words;
}

QString  Interpreter::whatIs(QString word){
    QString strAux;

    if(keyWords.contains(word)){
        strAux="keyWord";

    } else if (operators.contains(word)) {
        strAux="operator";

    } else if (word=="{"){
        strAux="startScope";

    } else if (word == "}"){
        strAux="endScope";

    } else if(word=="cout" ||word=="print" ||word=="printf"){
        strAux="stdKey";

    } else if(word=="("){
        strAux="bracketStart";

    } else if(word==")"){
        strAux="bracketFinal";

    } else if(word=="-endl") {
        strAux="end";

    } else if(word=="dot"){
        strAux="accessTo";

    } else if(word=="->"){
        strAux="error";

    } else{
        strAux="variable";
    }

    return strAux;
}

void Interpreter::interpretCode(int line){
    if (line<words.size()){
        if(words[line].size()==1){
            if(words[line][0]=="{"){
                //Abrir Scope
            } else if (words[line][0]=="}"){
                //Usar Garbage Collector
            }
        } else if (words[line].size()==2) {
            if(words[line][0]=="struct" && whatIs(words[line][1])=="variable"){
                //Declarar Struct con el nombre de la variable
            } else {
                //Error
            }

        } else {
            //qDebug()<<"Starting...";
            //qDebug()<<whatIs(words[line][words[line].size()-1]);

            if (whatIs(words[line][words[line].size()-1])=="end"){
                //qDebug()<<whatIs(words[line][0]);
                if(whatIs(words[line][0])=="keyWord"){
                    //qDebug()<<whatIs(words[line][1]);
                    if(whatIs(words[line][1]) =="variable" /*&& !isExisting(words[line][1])*/) {
                        //qDebug()<<whatIs(words[line][2]);
                        if (whatIs(words[line][2])=="end") {
                            //qDebug()<<"Declaration without definition";

                            QString type = words[line][0];
                            QString label = words[line][1];
                            QString Value = "null";

                            qDebug()<<type<<label<<Value;


                        } else if(whatIs(words[line][2])=="operator" && words[line][2]=="equals"){
                            //qDebug()<<whatIs(words[line][3]);
                            if(whatIs(words[line][3])=="variable" /*&& isExisting(words[line][3])*/){
                                qDebug()<<"3 caminos: número, char o variable";

                                if(isNumber(words[line][3])) {
                                    qDebug()<<"Número";
                                    if(whatIs(words[line][4])=="end"){

                                        QString type = words[line][0];
                                        QString label = words[line][1];
                                        QString Value = words[line][3];

                                        qDebug()<<type<<label<<Value;



                                        } else if(whatIs(words[line][4])=="operator") {
                                            if(words[line][4]=="+" || words[line][4]=="-" || words[line][4]=="*" || words[line][4]=="/"){
                                                if(whatIs(words[line][5])=="end"){
                                                    //Error
                                                } else if (isNumber(words[line][5])) {
                                                    if(whatIs(words[line][6])=="end"){
                                                        qDebug()<<"Hola mundo";
                                                } else {
                                                    //Error
                                                }
                                            } else {
                                                //Error
                                            }
                                        } else {
                                            //Error
                                        }

                                    } else {

                                    }
                                } else if(isChar(words[line][3])) {
                                    qDebug()<<"Char";
                                    if(whatIs(words[line][4])=="end"){
                                        QString type = words[line][0];
                                        QString label = words[line][1];
                                        QString Value = words[line][3];

                                        qDebug()<<type<<label<<Value;

                                    } else if(whatIs(words[line][4])=="operator" && words[line][4]=="+"){

                                        if(true){ // comparar con el siguiente elemento

                                        }

                                    } else {
                                        //Error
                                    }

                                } else if (words[line][3].contains("\"")) {
                                    //Error

                                } else { //Variable guardada en memoria
                                    //Buscar variable en memoria
                                }
                            }

                        }  else{
                            //Error
                        }

                    } else{
                        //Error
                    }


                    /*if(isExisting(words[line][3])){
                    //if(words[line][0]=="int"){


                    } else if(words[line][0]=="long"){

                    } else if(words[line][0]=="char"){

                    } else if(words[line][0]=="float"){

                    } else if(words[line][0]=="double"){

                    } else if(words[line][0]=="struct"){

                    } else if(words[line][0]=="reference"){

                    } else {
                        //Error
                    }*/

                } else if(whatIs(words[line][0])=="variable") {

                    //Buscar si existe y si no, tirar error

                } else if(whatIs(words[line][0])=="stdKey"){
                    //Printear en la terminal

                } else{
                    //Error
                }

            } else {
                //Error
            }

        }
        qDebug()<<words[line]<<"\n";
    }
}

void Interpreter::showCode(){
    for (int i = 0; i<words.size(); i++){
        qDebug()<<words[i];
    }
}

bool Interpreter::isExisting(QString variable){
    if(variable==""){
        return true;
    }
    return true;
}

bool Interpreter::isNumber(QString value){
    bool aux = true;
    bool dotOne = true;

    for(int i = 0; i<value.size(); i++){
        QString a = ".";
        aux = value[i].isDigit();

        if(value[value.size()-1]==a[0]){
            dotOne=false;
            aux=false;
        }

        if(!aux){
            if(value[i]==a[0] && dotOne){
                aux=true;
                dotOne=false;

            } else {
                break;
            }
        }
    }

    return aux;
}

bool Interpreter::isChar(QString value){
    bool aux = value.startsWith("\"")&& value.endsWith("\"") && value.count("\"")==2;
    return aux;
}

