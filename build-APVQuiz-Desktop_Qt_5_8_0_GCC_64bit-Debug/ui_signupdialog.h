/********************************************************************************
** Form generated from reading UI file 'signupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPDIALOG_H
#define UI_SIGNUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUpDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLabel *confirmPasswordLabel;
    QLineEdit *passwordLineEdit;
    QLineEdit *usernameLineEdit;
    QLineEdit *confirPasswordLineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *SignUpDialog)
    {
        if (SignUpDialog->objectName().isEmpty())
            SignUpDialog->setObjectName(QStringLiteral("SignUpDialog"));
        SignUpDialog->resize(947, 683);
        formLayoutWidget = new QWidget(SignUpDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(270, 190, 371, 451));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        usernameLabel = new QLabel(formLayoutWidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, usernameLabel);

        passwordLabel = new QLabel(formLayoutWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, passwordLabel);

        confirmPasswordLabel = new QLabel(formLayoutWidget);
        confirmPasswordLabel->setObjectName(QStringLiteral("confirmPasswordLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, confirmPasswordLabel);

        passwordLineEdit = new QLineEdit(formLayoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, passwordLineEdit);

        usernameLineEdit = new QLineEdit(formLayoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, usernameLineEdit);

        confirPasswordLineEdit = new QLineEdit(formLayoutWidget);
        confirPasswordLineEdit->setObjectName(QStringLiteral("confirPasswordLineEdit"));
        confirPasswordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, confirPasswordLineEdit);

        pushButton = new QPushButton(formLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, pushButton);

#ifndef QT_NO_SHORTCUT
        usernameLabel->setBuddy(usernameLineEdit);
        passwordLabel->setBuddy(passwordLineEdit);
        confirmPasswordLabel->setBuddy(confirPasswordLineEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(usernameLineEdit, passwordLineEdit);
        QWidget::setTabOrder(passwordLineEdit, confirPasswordLineEdit);
        QWidget::setTabOrder(confirPasswordLineEdit, pushButton);

        retranslateUi(SignUpDialog);

        QMetaObject::connectSlotsByName(SignUpDialog);
    } // setupUi

    void retranslateUi(QDialog *SignUpDialog)
    {
        SignUpDialog->setWindowTitle(QApplication::translate("SignUpDialog", "Dialog", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("SignUpDialog", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("SignUpDialog", "Password", Q_NULLPTR));
        confirmPasswordLabel->setText(QApplication::translate("SignUpDialog", "Confirm Password", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SignUpDialog", "Continue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignUpDialog: public Ui_SignUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPDIALOG_H
