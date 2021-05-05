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

    int aux;
    std::cout<<"1, sever. 2 client"<<std::endl;
    std::cin>>aux;

    if(aux ==1){

        Server* test = new Server;
        test->Start();

    } else if (aux == 2) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
