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

        /*!
         * @brief Método contructor del interprete
         */
        Interpreter();

        /*!
         * @brief Método constructor del interprete
         * @param terminalOutput Cuadro de texto de la terminal
         * @param _appLog Cuadro de texto del logger
         */
        Interpreter(QPlainTextEdit* terminalOutput, QPlainTextEdit* _appLog);

        /*!
         * @brief Método destructor del interpreter
         */
        ~Interpreter();

        /*!
         * @brief Se encarga de reorganizar el código de forma que sea entendible para el interprete
         * @param code Código escrito en el programa
         */
        void readCode(QString code);

        /*!
         * @brief Devuelve la lista de todas las palabras escritas en el código
         * @return QList<QStringList>
         */
        QList<QStringList> getWords();

        /*!
         * @brief Este método se encarga de comparar qué clase de cadena es la que está leyendo
         * @param word Palabra que se quiere comparar
         * @return QString
         */
        QString whatIs(QString word);

        /*!
         * @brief Es el método que permite interpretar el contenido del código escrito
         * @param line Es el número de linea de código que está interpretando
         */
        void interpretCode(int line);

        /*!
         * @brief Permite mostrar el código reinterpretado en consola
         */
        void showCode();

        /*!
         * @brief Le pregunta al servidor el tipo del dato introducido
         * @param aux Nombre de la variable
         * @return QString
         */
        QString askFor(QString aux);

        /*!
         * @brief Método que permite determinar si una cadena de texto es un número
         * @param value Parámetro con un valor
         * @return bool
         */
        bool isNumber(QString value);

        /*!
         * @brief Método que permite determinar si una cadena de texto es un char
         * @param value Parámetro con un valor
         * @return bool
         */
        bool isChar(QString value);

        /*!
         * @brief Permite detectar si la cadena brindada pertenece al nombre de un struct
         * @param aux Cadena de texto con el nombre de la variable
         * @return bool
         */
        bool isStruct(QString aux);

        /*!
         * @brief Permite al interpreter tener acceso a la terminal
         * @param terminalOutput Terminal del IDE
         */
        void setTerminal(QPlainTextEdit* terminalOutput);

        /*!
         * @brief Permite al interpreter tener acceso al logger
         * @param newAppLog Logger del IDE
         */
        void setAppLog(QPlainTextEdit* newAppLog);

        /*!
         * @brief Muestra un mensaje en la terminal
         * @param msg Mensaje recibido
         */
        void showInTerminal(QString msg);

        /*!
         * @brief Muestra un mensaje en el logger
         * @param msg Mensaje recibido
         */
        void showInAppLog(QString msg);

        /*!
         * @brief Libera el scope
         */
        void freeScope();

        /*!
         * @brief Permite liberar scopes
         * @param freeingScope Valor para freeingScope
         */
        void setFreeingScope(bool freeingScope);

        /*!
         * @brief Permite obtener el estado del scope
         * @return bool
         */
        bool isFreeingScope() const;

        /*!
         * @brief Permite saber cuales son las variables declaradas dentro del scope
         * @return QStringList
         */
        const QStringList &getScopeLabels() const;

        /*!
         * @brief Permite saber si hay un scope abierto
         * @return bool
         */
        bool isScope() const;

        /*!
         * @brief Permite decirle al servidor que declare variables al conocer sus datos
         * @param type Tipo de dato de la variable
         * @param label Etiqueta de la variable
         * @param Value Valor de la variable
         */
        void toDeclarate(QString type, QString label, QString Value);

        /*!
         * @brief Permite determinar si una variable es atributo de una estructura
         * @param name Nombre de la estructura
         * @param attribute Nombre del atributo de la estructura
         * @return QString
         */

        QString isAttribute(QString name,QString attribute);
        bool isStopProgram() const;
        void setStopProgram(bool stopProgram);


private:
    bool freeingScope = false;
    bool inScope= false;
    bool scope = true;
    bool stopProgram = false;

    QStringList scopeLabels;
    QPlainTextEdit *terminal;
    QPlainTextEdit *appLog;
    QStringList keyWords;
    QStringList operators;
    QList<QStringList> words;
    QList<QList<QStringList>> structList;
    QList<QStringList> structs;
    QStringList auxStructs;
    bool inStruct = false;
    Client *client;

public:
    void setClient(Client *client);
    QString getValue(QString aux);

};


#endif //IDE_INTERPRETER_H
