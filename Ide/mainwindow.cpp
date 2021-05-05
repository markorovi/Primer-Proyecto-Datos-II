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

/// Método principal del MainWindow
/// \param parent QWidget
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
    interpreter.setClient(test);

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

    QJsonDocument doc;
    doc.setObject(Parser::Nothing()); //Genera el documento con los rasgos de dentro
    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
    MainWindow::setJson(Json);

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
/// Destructor del método del MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

/// Permite mostrar valores en la tabla que contiene los valores de la memoria ram
/// \param memoryDirection QString dirección de memoria
/// \param value QString valor de la variable ingresada
/// \param label QString nombre de la variable ingresada
/// \param referenceCount QString cantidad de veces que ha sido referenciada la variable ingresada
void MainWindow::setValuesRamLiveView(QString memoryDirection, QString value,  QString label, int referenceCount)
{

    int aux = -1;
//    qDebug()<<ui->ramLiveView->rowCount();

    for(int i = 0; i<ui->ramLiveView->rowCount(); i++){

        if (ui->ramLiveView->item(i,2)->text()==label){
            aux=i;
        }
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

    for(int i = 0; i<ui->ramLiveView->rowCount(); i++){

        if (ui->ramLiveView->item(i,2)->text()==""){
            ui->ramLiveView->removeRow(i);
        }
    }
}

///Permite abrir archivos de texto al abrir tocar un botón
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

/// Permite guardar el código escrito al pulsar un botón
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

///Permite cerrar el programa al pulsar un botón
void MainWindow::on_actionClose_triggered()
{
    close();
}

/// Ejecuta el código escrito al pulsar un botón
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
        //interpreter.showCode();
        interpreter.interpretCode(line);


        test->Start();
        line++;
        if(interpreter.isScope() || QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(),"toDo"))!="nothing"){
            setValuesRamLiveView(QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "address")),
                                 QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "value")),
                                 QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(), "name")),0);
        }
    } else {
        on_actionStop_triggered();
        on_actionRun_triggered();
    }

    QJsonDocument doc;
    doc.setObject(Parser::Nothing()); //Genera el documento con los rasgos de dentro
    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
    MainWindow::setJson(Json);
}

///Detiene el funcionamiento del código al pulsar un botón
void MainWindow::on_actionStop_triggered()
{
    if(running){
        running=false;
        line=0;
        interpreter=Interpreter(ui->terminalOutput, ui->appLog);
        interpreter.setClient(test);


        ui->ramLiveView->setRowCount(0);
        interpreter.showInTerminal("The program has unexpectedly finished\n");
        qDebug()<<"\n"<<"The program has unexpectedly finished\n";
    }
}

///Permite leer la siguiente linea del codigo al pulsar un botón
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



            if(!interpreter.isFreeingScope() || QString::fromStdString(Parser::ReturnStringValueFromJson(Client::getReceived(),"toDo"))!="nothing"){
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
            interpreter.showInAppLog("El programa ha finalizado");
            on_actionStop_triggered();
        }

    }
    QJsonDocument doc;
    doc.setObject(Parser::Nothing()); //Genera el documento con los rasgos de dentro
    std::string Json = Parser::ReturnChar(doc); //String to char (to be able to send it through sockets) //Lo pasa a string
    MainWindow::setJson(Json);

}

/// Permite a la ventana principal obtener un Json para enviar al servidor por medio del cliente
/// \return std::string
std::string MainWindow::getJson() {
    return json;
}

/// Permite a la ventana principal establecer un Json para enviar al servidor por medio del cliente
/// \param toSet std::string valor que se va a poner al Json
void MainWindow::setJson(std::string toSet) {
    json = toSet;
}

