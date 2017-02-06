/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *usernameTextEdit;
    QTextEdit *passwordTextEdit;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QPushButton *logInPushButton;
    QPushButton *pushButton_2;
    QLabel *offlineLabel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        usernameTextEdit = new QTextEdit(centralWidget);
        usernameTextEdit->setObjectName(QStringLiteral("usernameTextEdit"));
        usernameTextEdit->setGeometry(QRect(160, 60, 131, 31));
        passwordTextEdit = new QTextEdit(centralWidget);
        passwordTextEdit->setObjectName(QStringLiteral("passwordTextEdit"));
        passwordTextEdit->setGeometry(QRect(160, 100, 131, 31));
        usernameLabel = new QLabel(centralWidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(80, 60, 71, 31));
        passwordLabel = new QLabel(centralWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(80, 100, 71, 31));
        logInPushButton = new QPushButton(centralWidget);
        logInPushButton->setObjectName(QStringLiteral("logInPushButton"));
        logInPushButton->setGeometry(QRect(160, 140, 89, 25));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 170, 89, 25));
        offlineLabel = new QLabel(centralWidget);
        offlineLabel->setObjectName(QStringLiteral("offlineLabel"));
        offlineLabel->setGeometry(QRect(76, 10, 221, 41));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        logInPushButton->setText(QApplication::translate("MainWindow", "Log in", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Sign up", Q_NULLPTR));
        offlineLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
