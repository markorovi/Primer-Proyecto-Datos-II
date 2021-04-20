#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    /*QStringList stringList;
    stringList.append("Hellouda");
    stringList.append("aaaaaaaaaaaaaaaaaa");
    stringList.append("\" Hola \"");
    stringList.append("soy");
    stringList.append("Joel");
    stringList.append("Gomez \"");
    stringList.append("eeeeeeeeeeeeeeeeeeee");
    qDebug()<<stringList;
    qDebug()<<stringList[2].count("\"");
    stringList[1]=stringList[1]+stringList[2];
    stringList.remove(2);
    qDebug()<<stringList;*/

    return a.exec();
}
