//
// Created by joel on 19/4/21.
//

#ifndef IDE_INTERPRETER_H
#define IDE_INTERPRETER_H
#include <QStandardItemModel>
#include <QString>

class Interpreter {
    public:
        Interpreter();

        void readCode(QString);

    private:
        QStringList keyWords;
        QStringList operators;

};


#endif //IDE_INTERPRETER_H
