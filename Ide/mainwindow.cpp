#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableView>

#include <QStandardItemModel>
#include <QString>

#include "Interpreter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("C! - IDE");



    //Code Input

    QString code = ui->codeInput->toPlainText();
    int linesCount = code.count("\n");



    for (int i=0; i<linesCount; i++) {
        ui->labelNumberLine->setText(ui->labelNumberLine->text() + "\n" + QString().setNum(i+2));
    }

    //qDebug()<<ui->labelNumberLine->text();


    //Interprete
    Interpreter interpreter = Interpreter();
    interpreter.readCode(code);



    //Live Ram View

    ui->ramLiveView->setColumnCount(4);
    QStringList l;
    l<<"Direccion"<<"Valor"<<"Etiqueta"<<"Referencias";
    ui->ramLiveView->setHorizontalHeaderLabels(l);

    ui->ramLiveView->setColumnWidth(0,100);
    ui->ramLiveView->setColumnWidth(1,60);
    ui->ramLiveView->setColumnWidth(2,90);
    ui->ramLiveView->setColumnWidth(3,100);

    for (int i =0; i<10; i++)
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
