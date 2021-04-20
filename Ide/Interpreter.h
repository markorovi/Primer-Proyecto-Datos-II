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
        ~Interpreter();
        void readCode(QString);
        QList<QStringList> getWords();

        void interpretCode(int);

    private:
        QStringList keyWords;
        QStringList operators;
        QList<QStringList> words;
};


#endif //IDE_INTERPRETER_H
