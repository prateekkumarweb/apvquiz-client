/********************************************************************************
** Form generated from reading UI file 'firstwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTWINDOW_H
#define UI_FIRSTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FirstWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginPushButton;
    QPushButton *signUpPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FirstWindow)
    {
        if (FirstWindow->objectName().isEmpty())
            FirstWindow->setObjectName(QStringLiteral("FirstWindow"));
        FirstWindow->resize(949, 677);
        centralWidget = new QWidget(FirstWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(320, 120, 301, 321));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        usernameLabel = new QLabel(groupBox);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        horizontalLayout->addWidget(usernameLabel);

        usernameLineEdit = new QLineEdit(groupBox);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        horizontalLayout->addWidget(usernameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        passwordLabel = new QLabel(groupBox);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        horizontalLayout_2->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(groupBox);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(passwordLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        loginPushButton = new QPushButton(groupBox);
        loginPushButton->setObjectName(QStringLiteral("loginPushButton"));

        verticalLayout->addWidget(loginPushButton);

        signUpPushButton = new QPushButton(groupBox);
        signUpPushButton->setObjectName(QStringLiteral("signUpPushButton"));

        verticalLayout->addWidget(signUpPushButton);

        signUpPushButton->raise();
        loginPushButton->raise();
        FirstWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FirstWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 949, 22));
        FirstWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FirstWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FirstWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FirstWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FirstWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        usernameLabel->setBuddy(usernameLineEdit);
        passwordLabel->setBuddy(passwordLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(FirstWindow);

        QMetaObject::connectSlotsByName(FirstWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FirstWindow)
    {
        FirstWindow->setWindowTitle(QApplication::translate("FirstWindow", "FirstWindow", Q_NULLPTR));
        groupBox->setTitle(QString());
        usernameLabel->setText(QApplication::translate("FirstWindow", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("FirstWindow", "Password", Q_NULLPTR));
        loginPushButton->setText(QApplication::translate("FirstWindow", "Login", Q_NULLPTR));
        signUpPushButton->setText(QApplication::translate("FirstWindow", "Sign Up", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FirstWindow: public Ui_FirstWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTWINDOW_H
