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

void Interpreter::readCode(QString code){

    QStringList lines = code.split("\n");
    lines.removeAll("");

    QList<QStringList> words;


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



    for (int i = 0; i<words.size(); i++){
        qDebug()<<words[i];
    }
}
