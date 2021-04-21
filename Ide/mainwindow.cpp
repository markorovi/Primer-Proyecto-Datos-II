#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableView>

#include <QStandardItemModel>
#include <QString>

#include "Interpreter.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("C! - IDE");



    //Code Input

    QString code = ui->codeInput->toPlainText();


    //Interpreter
    //interpreter.readCode(code);
    //interpreter.showCode();
    //interpreter = Interpreter();



    //Live Ram View

    ui->ramLiveView->setColumnCount(4);
    QStringList l;
    l<<"Direccion"<<"Valor"<<"Etiqueta"<<"Referencias";
    ui->ramLiveView->setHorizontalHeaderLabels(l);

    ui->ramLiveView->setColumnWidth(0,100);
    ui->ramLiveView->setColumnWidth(1,60);
    ui->ramLiveView->setColumnWidth(2,90);
    ui->ramLiveView->setColumnWidth(3,100);

    for (int i =0; i<5; i++)
    {
        setValuesRamLiveView("0x999","10","a",2);
        setValuesRamLiveView("0x998","11","b",1);
        setValuesRamLiveView("0x997","12","c",4);
        setValuesRamLiveView("0x996","13","d",3);
        setValuesRamLiveView("0x995","14","e",6);
    }

    //Elimina las filas de la tabla
    //ui->ramLiveView->setRowCount(0);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setValuesRamLiveView(QString memoryDirection, QString value,  QString label, int referenceCount)
{
    ui->ramLiveView->insertRow(ui->ramLiveView->rowCount());

    ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 0, new QTableWidgetItem(memoryDirection));
    ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 1, new QTableWidgetItem(value));
    ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 2, new QTableWidgetItem(label));
    ui->ramLiveView->setItem(ui->ramLiveView->rowCount()-1, 3, new QTableWidgetItem(QString::number(referenceCount)));

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
    if(!running){
        ui->terminalOutput->appendPlainText("\n>> The program is starting\n");
        qDebug()<<"\n"<<"The program is starting\n";

        running=true;
        interpreter.readCode(ui->codeInput->toPlainText());
        interpreter.interpretCode(line);
        line++;
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
        interpreter=Interpreter();
        ui->terminalOutput->appendPlainText("\n>> The program has unexpectedly finished\n");
        qDebug()<<"\n"<<"The program has unexpectedly finished\n";
    }
}

void MainWindow::on_actionNext_Line_triggered()
{
    if(running){
        if(line<interpreter.getWords().size()){
            interpreter.interpretCode(line);
            line++;
        } else {
            on_actionStop_triggered();
        }

    }
}
