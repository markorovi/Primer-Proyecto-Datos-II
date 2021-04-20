/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave_as;
    QAction *actionClose;
    QAction *actionRun;
    QAction *actionStop;
    QAction *actionNext_Line;
    QWidget *centralwidget;
    QPlainTextEdit *codeInput;
    QPlainTextEdit *appLog;
    QTableWidget *ramLiveView;
    QLabel *labelConsole;
    QLabel *labelLog;
    QLabel *labelNumberLine;
    QPlainTextEdit *terminalOutput;
    QMenuBar *menubar;
    QMenu *menuVuild;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(2104, 984);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../Descargas/iconfinder_folder-open-storage-file-organize_3209339.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../Descargas/iconfinder_158-Save_2123968.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon1);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../Descargas/iconfinder_circle_close_cancel_exit_quit_delete_4831037.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon2);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../Descargas/iconfinder_icon-play_211876.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon3);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../Descargas/iconfinder_interface-solid-multimedia-stop-button-1_6127256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon4);
        actionNext_Line = new QAction(MainWindow);
        actionNext_Line->setObjectName(QString::fromUtf8("actionNext_Line"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../Descargas/iconfinder_right_4_1_4829859.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext_Line->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        codeInput = new QPlainTextEdit(centralwidget);
        codeInput->setObjectName(QString::fromUtf8("codeInput"));
        codeInput->setGeometry(QRect(60, 10, 1431, 471));
        appLog = new QPlainTextEdit(centralwidget);
        appLog->setObjectName(QString::fromUtf8("appLog"));
        appLog->setGeometry(QRect(10, 720, 1481, 151));
        appLog->setReadOnly(true);
        ramLiveView = new QTableWidget(centralwidget);
        ramLiveView->setObjectName(QString::fromUtf8("ramLiveView"));
        ramLiveView->setGeometry(QRect(1510, 10, 411, 861));
        labelConsole = new QLabel(centralwidget);
        labelConsole->setObjectName(QString::fromUtf8("labelConsole"));
        labelConsole->setGeometry(QRect(10, 510, 67, 17));
        labelConsole->setAlignment(Qt::AlignCenter);
        labelLog = new QLabel(centralwidget);
        labelLog->setObjectName(QString::fromUtf8("labelLog"));
        labelLog->setGeometry(QRect(10, 700, 67, 17));
        labelLog->setAlignment(Qt::AlignCenter);
        labelNumberLine = new QLabel(centralwidget);
        labelNumberLine->setObjectName(QString::fromUtf8("labelNumberLine"));
        labelNumberLine->setGeometry(QRect(20, 15, 31, 471));
        labelNumberLine->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        terminalOutput = new QPlainTextEdit(centralwidget);
        terminalOutput->setObjectName(QString::fromUtf8("terminalOutput"));
        terminalOutput->setGeometry(QRect(10, 530, 1481, 151));
        terminalOutput->setMouseTracking(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 2104, 22));
        menuVuild = new QMenu(menubar);
        menuVuild->setObjectName(QString::fromUtf8("menuVuild"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuVuild->menuAction());
        menuVuild->addAction(actionRun);
        menuVuild->addAction(actionStop);
        menuVuild->addAction(actionNext_Line);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave_as);
        toolBar->addSeparator();
        toolBar->addAction(actionRun);
        toolBar->addAction(actionStop);
        toolBar->addAction(actionNext_Line);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_as->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("MainWindow", "Close", nullptr));
#ifndef QT_NO_SHORTCUT
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionRun->setText(QApplication::translate("MainWindow", "Run", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRun->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_NO_SHORTCUT
        actionStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        actionNext_Line->setText(QApplication::translate("MainWindow", "Next Line", nullptr));
        codeInput->setPlainText(QApplication::translate("MainWindow", "int a = 3;\n"
"\n"
"int b = 5;\n"
"\n"
"int suma = a + b;\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"", nullptr));
        labelConsole->setText(QApplication::translate("MainWindow", "Console", nullptr));
        labelLog->setText(QApplication::translate("MainWindow", "Log", nullptr));
        labelNumberLine->setText(QApplication::translate("MainWindow", "1", nullptr));
        terminalOutput->setPlainText(QApplication::translate("MainWindow", ">>", nullptr));
        menuVuild->setTitle(QApplication::translate("MainWindow", "Build", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
