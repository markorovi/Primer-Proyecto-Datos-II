#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "../Sockets/Client.h"
#include "../Sockets/Server.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

//    int aux;
//    std::cout<<"1, sever. 2 client"<<std::endl;
//    std::cin>>aux;

//    if(aux ==1){
//        Server* test = new Server;
//        test->Initialize();
//        test->Start();
//    } else if (aux == 2) {
//        Client *test = new Client;
//        test->Initialize();
//        test->Start();
//    }
        //Generating and parsing QJsonDocument
        QJsonDocument doc;
        QJsonObject obj;
        obj["test"] = "respuesta";
        obj["test1"] = "respuesta1";
        obj["test2"] = "respuesta2";
        obj["test3"] = "respuesta3";
        doc.setObject(obj);
        QString strJson(doc.toJson(QJsonDocument::Compact)); //QJsonDocument to QString
        std::string test =  strJson.toUtf8().constData(); //QString to string
        const char * prueba= test.c_str(); //String to char (to be able to send it through sockets)

        //Getting data from de char received on the socket
        std::string final = static_cast<std::string>(prueba); //Char to string
        QString test2 = QString::fromUtf8(test.c_str()); //String to QString
        QJsonDocument doc2 = QJsonDocument::fromJson(test2.toUtf8()); //QString to QJsonDocument
        std::string respuesta = doc2.object().value(QString("test")).toString().toUtf8().constData(); //Getting the value of "test" on a string
        std::cout<<respuesta;
}
