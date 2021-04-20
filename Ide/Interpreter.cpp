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
    operators.append("=");



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
                words[i].append(".");
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
           }

           if(words[i][j].contains("getaddr")){
               QStringList aux = words[i][j].split("(");
               words[i][j]=aux[0];
               words[i].insert(j+1, "(");
               aux = aux[1].split(")");
               words[i].insert(j+2, aux[0]);
               words[i].insert(j+3, ")");
           }
       }
   }

    /*for (int i = 0; i<words.size(); i++){
        qDebug()<<words[i];
    }*/
}

QList<QStringList> Interpreter::getWords(){
    return words;
}

void Interpreter::interpretCode(int line){
    if (line<words.size()){
        qDebug()<<words[line];
    }
}
