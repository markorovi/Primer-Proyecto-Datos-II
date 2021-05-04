#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableView>

#include <QStandardItemModel>
#include <QString>

#include "Interpreter.h"
#include "../Sockets/Client.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

std::string MainWindow::json = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("C! - IDE");

    //Code Input

    QString code = ui->codeInput->toPlainText();

    //Interpreter
    interpreter = Interpreter(ui->terminalOutput, ui->appLog);
//    interpreter.readCode(code);
//    interpreter.showCode();


    //Live Ram View

    ui->ramLiveView->setColumnCount(4);
    QStringList l;
    l<<"Direccion"<<"Valor"<<"Etiqueta"<<"Referencias";
    ui->ramLiveView->setHorizontalHeaderLabels(l);

    ui->ramLiveView->setColumnWidth(0,150);
    ui->ramLiveView->setColumnWidth(1,60);
    ui->ramLiveView->setColumnWidth(2,90);
    ui->ramLiveView->setColumnWidth(3,100);

//    for (int i =0; i<5; i++)
//    {
//        setValuesRamLiveView("0x999","10","a",2);
//        setValuesRamLiveView("0x998","11","b",1);
//        setValuesRamLiveView("0x997","12","c",4);
//        setValuesRamLiveView("0x996","13","d",3);
//        setValuesRamLiveView("0x995","14","e",6);
//    }

    //Elimina las filas de la tabla
    //ui->ramLiveView->setRowCount(0);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setValuesRamLiveView(QString memoryDirection, QString value,  QString label, int referenceCount)
{

    int aux = -1;
//    qDebug()<<ui->ramLiveView->rowCount();

    for(int i = 0; i<ui->ramLiveView->rowCount(); i++){
        //qDebug()<<"El elemento"<<i<<"es:"<<ui->ramLiveView->item(i,2)->text();
        //qDebug()<<"Last: "<<ui->ramLiveView->item(ui->ramLiveView->rowCount()-1,2)->text();
        if (ui->ramLiveView->item(i,2)->text()==label){
            aux=i;
//            qDebug()<<aux;
        }

//        if(ui->ramLiveView->item(ui->ramLiveView->rowCount()-1,2)->text()==label) {
//            aux = ui->ramLiveView->rowCount()-1;
//            qDebug()<<"hola";
//        }
    }


    if(aux==-1){
        ui->ramLiveView->insertRow(ui->ramLiveView->rowCount());

        ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 0, new QTableWidgetItem(memoryDirection));
        ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 1, new QTableWidgetItem(value));
        ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 2, new QTableWidgetItem(label));
        ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 3, new QTableWidgetItem(QString::number(referenceCount)));

    } else {
        ui->ramLiveView->setItem(aux, 0, new QTableWidgetItem(memoryDirection));
        ui->ramLiveView->setItem(aux, 1, new QTableWidgetItem(value));
        ui->ramLiveView->setItem(aux, 2, new QTableWidgetItem(label));
        ui->ramLiveView->setItem(aux, 3, new QTableWidgetItem(QString::number(referenceCount)));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFile file;
    QTextStream io;

    QString filename = QFileDialog::getOpenFileName(this, "Abrir");
    file.setFileName(filename);

    if(filename.isEmpty()){
        return;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.isOpen()){
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    io.setDevice(&file);
    ui->codeInput->setPlainText(io.readAll());

    file.close();


}

void MainWindow::on_actionSave_as_triggered()
{
    QFile file;
    QTextStream io;
    QString filename = QFileDialog::getSaveFileName(this,"Guardar");

    file.setFileName(filename);

    if(filename.isEmpty()){
        return;
    }

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (!file.isOpen()){
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    io.setDevice(&file);
    io<<ui->codeInput->toPlainText();

    file.flush();
    file.close();
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionRun_triggered()
{

//    qDebug()<<"Line:"<<line;
    if(!running){

        line=0;
        interpreter.showInTerminal("The program is starting\n");
        qDebug()<<"\n"<<"The program is starting\n";

        ui->ramLiveView->removeRow(0);
        running=true;
        interpreter.readCode(ui->codeInput->toPlainText());
        interpreter.interpretCode(line);


        test->Start();
        line++;
        if(interpreter.isScope()){
            setValuesRamLiveView(QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "address")),
                                 QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value")),
                                 QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "name")),0);
        }
    } else {
        on_actionStop_triggered();
        on_actionRun_triggered();
    }
}

void MainWindow::on_actionStop_triggered()
{
    if(running){
        running=false;
        line=0;
        interpreter=Interpreter(ui->terminalOutput, ui->appLog);

        ui->ramLiveView->setRowCount(0);
        interpreter.showInTerminal("The program has unexpectedly finished\n");
        qDebug()<<"\n"<<"The program has unexpectedly finished\n";
    }
}

void MainWindow::on_actionNext_Line_triggered()
{
    //interpreter.showInAppLog("El programa se está ejecutando");
    //qDebug()<<"Actual line:"<<line;
    if(running){

        if(line<interpreter.getWords().size()){

            interpreter.showInAppLog("El programa está leyendo las instrucciones");
            interpreter.interpretCode(line);

            test->Start();
            usleep(10000);
            line++;



            if(!interpreter.isFreeingScope()){
                setValuesRamLiveView(QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "address")),
                                     QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value")),
                                     QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "name")),0);
            }

            if(interpreter.isFreeingScope()) {
                QJsonDocument doc;
                for (int i = 0; i < interpreter.getScopeLabels().size(); i++) {
                    // liberar memoria con el garbage collector
                    doc.setObject(Parser::CreateJsonObj_Free(interpreter.getScopeLabels()[i].toStdString()));
                    std::string json = Parser::ReturnChar(doc);
                    MainWindow::setJson(json);

                    for (int j=0;j<ui->ramLiveView->rowCount();j++){
                        //qDebug()<<"Mensaje de prueba tabla de Ram: "<<ui->ramLiveView->item(j,2)->text();
                        if(ui->ramLiveView->item(j,2)->text()==interpreter.getScopeLabels()[i]){
                            ui->ramLiveView->removeRow(j);
                        }

                    }

                    test->Start();
                    usleep(10000);
                }
                qDebug("Liberando memoria");
                doc.setObject(Parser::Nothing());
                interpreter.setFreeingScope(false);
            }

        } else {
            interpreter.showInAppLog("Hmmmmmm... algo está mal");
            on_actionStop_triggered();
        }

    }

}

std::string MainWindow::getJson() {
    return json;
}

void MainWindow::setJson(std::string toSet) {
    json = toSet;
}

