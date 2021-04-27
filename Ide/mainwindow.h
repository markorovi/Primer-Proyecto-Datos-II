#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Interpreter.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setValuesRamLiveView(QString , QString, QString, int);

private:
    int line=0;
    bool running=false;
    Interpreter interpreter = Interpreter();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_as_triggered();
    void on_actionClose_triggered();
    void on_actionRun_triggered();
    void on_actionStop_triggered();
    void on_actionNext_Line_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
