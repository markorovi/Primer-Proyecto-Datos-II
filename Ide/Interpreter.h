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
    private:

        bool inScope= false;
        QStringList scopeLabels;

        QPlainTextEdit *terminal;
        QPlainTextEdit *appLog;
        QStringList keyWords;
        QStringList operators;
        QList<QStringList> words;
        bool scope = true;
public:
    bool isScope() const;
};


#endif //IDE_INTERPRETER_H
