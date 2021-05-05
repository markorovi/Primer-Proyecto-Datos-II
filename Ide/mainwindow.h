#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Interpreter.h"
#include <QMainWindow>
#include "../Sockets/Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * @brief Método principal del MainWindow
     * @param parent Objeto padre
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * @brief Destructor del método del MainWindow
     */
    ~MainWindow();

    /*!
     * @brief Permite mostrar valores en la tabla que contiene los valores de la memoria ram
     * @param memoryDirection Dirección de memoria
     * @param value Valor de la variable ingresada
     * @param label Nombre de la variable ingresada
     * @param referenceCount Cantidad de veces que ha sido referenciada la variable ingresada
     */
    void setValuesRamLiveView(QString memoryDirection, QString value, QString label, int referenceCount);

    /*!
     * @brief Permite a la ventana principal obtener un Json para enviar al servidor por medio del cliente
     * @return std::string
     */
    static std::string getJson();

    /*!
     * @brief Permite a la ventana principal establecer un Json para enviar al servidor por medio del cliente
     * @param toSet Valor que se va a poner al Json
     */
    static void setJson(std::string toSet);


private slots:
    void on_actionOpen_triggered();
    void on_actionSave_as_triggered();
    void on_actionClose_triggered();
    void on_actionRun_triggered();
    void on_actionStop_triggered();
    void on_actionNext_Line_triggered();

private:
    int line=0;
    bool running=false;
    Interpreter interpreter = Interpreter();
    static std::string json;


    Client *test = new Client;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
