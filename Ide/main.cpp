#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <thread>
#include "../Sockets/Client.h"
#include "../Sockets/Server.h"
#include "../Sockets/Parser.h"
#include <pthread.h>
#include "../Memory/Memory.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    int aux;
    std::cout<<"1, sever. 2 client"<<std::endl;
    std::cin>>aux;

    if(aux ==1){
        Server* test = new Server;
        //test->Initialize();
        test->Start();
    } else if (aux == 2) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
//        std::thread t1(&Client::Start, test);
//        t1.detach();
        return a.exec();
    }
        //Generating and parsing QJsonDocument

//        QJsonDocument doc;
//        doc.setObject(Parser::CreateJsonObj_NoAddress("int", "a", "22")); //Genera el documento con los rasgos de dentro
//        std::string prueba= Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
//
//        const char * prueba1 = prueba.c_str(); //Lo de la derecha de la desigualdad es como iria dentro del socket

//        QJsonDocument doc2 = Parser::ReturnJson(prueba1); //Devolver lo que llego por el socket a json
//        std::cout<<Parser::ReturnStringValueFromJson(doc, "name"); //Obtener un valor de json

/*    Memory::get_instance()->Need_Memory("int", "11", "hola");
    Memory::get_instance()->Need_Memory("int", "22", "hola1");
    Memory::get_instance()->Need_Memory("int", "33", "hola2");
    Memory::get_instance()->Need_Memory("int", "44", "hola3");
    Memory::get_instance()->Need_Memory("int", "55", "hola4");
    Memory::get_instance()->Need_Memory("int", "66", "hola5");
    Memory::get_instance()->Show();
    Memory::get_instance()->Freeing_Memory("hola");
    Memory::get_instance()->Show();
    Memory::get_instance()->Need_Memory("int", "77", "hola6");
    Memory::get_instance()->Show();*/

}
