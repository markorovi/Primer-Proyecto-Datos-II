//
// Created by joel on 19/4/21.
//

#ifndef IDE_INTERPRETER_H
#define IDE_INTERPRETER_H
#include <QStandardItemModel>
#include <QString>
#include <QPlainTextEdit>
#include <QDebug>
#include <QStringList>
#include "../Sockets/Client.h"

class Interpreter {
    public:
        Interpreter();
        Interpreter(QPlainTextEdit*, QPlainTextEdit*);
        ~Interpreter();
        void readCode(QString);
        QList<QStringList> getWords();
        QString whatIs(QString);
        void interpretCode(int);
        void showCode();

        bool isExisting(QString);
        bool isNumber(QString);
        bool isChar(QString);

        void setTerminal(QPlainTextEdit*);
        void setAppLog(QPlainTextEdit*);
        void showInTerminal(QString);
        void showInAppLog(QString);
        void freeScope();
        void setFreeingScope(bool freeingScope);
        bool isFreeingScope() const;
        const QStringList &getScopeLabels() const;
        bool isScope() const;

private:
    bool freeingScope = false;
    bool inScope= false;
    QStringList scopeLabels;
    QPlainTextEdit *terminal;
    QPlainTextEdit *appLog;
    QStringList keyWords;
    QStringList operators;
    QList<QStringList> words;
    QList<QStringList> structs;
    QStringList auxStructs;
    bool scope = true;
    bool inStruct = false;
};


#endif //IDE_INTERPRETER_H
