/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QLabel *utilityLabel;
    QWidget *formLayoutWidget;
    QFormLayout *opponentFormLayout;
    QLabel *opponenet1NameLabel;
    QLabel *opponent2NameLabel;
    QLabel *opponent3NameLabel;
    QLabel *opponentLabel;
    QLabel *opponent1Scorelabel;
    QLabel *opponent3Scorelabel;
    QLabel *opponent2Scorelabel;
    QLabel *opponentScoreLabel;
    QWidget *layoutWidget;
    QVBoxLayout *optionVerticalLayout;
    QPushButton *option1PushButton;
    QPushButton *option2PushButton;
    QPushButton *option3PushButton;
    QPushButton *option4PushButton;
    QLabel *timerLabel;
    QLabel *questionLabel;
    QWidget *widget;
    QHBoxLayout *scoreHorizontalLayout;
    QLabel *scoreStaticLabel;
    QLabel *scoreLabel;

    void setupUi(QDialog *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(902, 602);
        utilityLabel = new QLabel(GameWindow);
        utilityLabel->setObjectName(QStringLiteral("utilityLabel"));
        utilityLabel->setGeometry(QRect(46, 446, 801, 111));
        formLayoutWidget = new QWidget(GameWindow);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(660, 190, 241, 221));
        opponentFormLayout = new QFormLayout(formLayoutWidget);
        opponentFormLayout->setObjectName(QStringLiteral("opponentFormLayout"));
        opponentFormLayout->setContentsMargins(0, 0, 0, 0);
        opponenet1NameLabel = new QLabel(formLayoutWidget);
        opponenet1NameLabel->setObjectName(QStringLiteral("opponenet1NameLabel"));
        opponenet1NameLabel->setMinimumSize(QSize(150, 40));

        opponentFormLayout->setWidget(1, QFormLayout::LabelRole, opponenet1NameLabel);

        opponent2NameLabel = new QLabel(formLayoutWidget);
        opponent2NameLabel->setObjectName(QStringLiteral("opponent2NameLabel"));
        opponent2NameLabel->setMinimumSize(QSize(150, 40));

        opponentFormLayout->setWidget(2, QFormLayout::LabelRole, opponent2NameLabel);

        opponent3NameLabel = new QLabel(formLayoutWidget);
        opponent3NameLabel->setObjectName(QStringLiteral("opponent3NameLabel"));
        opponent3NameLabel->setMinimumSize(QSize(150, 40));

        opponentFormLayout->setWidget(3, QFormLayout::LabelRole, opponent3NameLabel);

        opponentLabel = new QLabel(formLayoutWidget);
        opponentLabel->setObjectName(QStringLiteral("opponentLabel"));
        opponentLabel->setMinimumSize(QSize(150, 40));

        opponentFormLayout->setWidget(0, QFormLayout::LabelRole, opponentLabel);

        opponent1Scorelabel = new QLabel(formLayoutWidget);
        opponent1Scorelabel->setObjectName(QStringLiteral("opponent1Scorelabel"));
        opponent1Scorelabel->setMinimumSize(QSize(50, 40));

        opponentFormLayout->setWidget(1, QFormLayout::FieldRole, opponent1Scorelabel);

        opponent3Scorelabel = new QLabel(formLayoutWidget);
        opponent3Scorelabel->setObjectName(QStringLiteral("opponent3Scorelabel"));
        opponent3Scorelabel->setMinimumSize(QSize(50, 40));

        opponentFormLayout->setWidget(3, QFormLayout::FieldRole, opponent3Scorelabel);

        opponent2Scorelabel = new QLabel(formLayoutWidget);
        opponent2Scorelabel->setObjectName(QStringLiteral("opponent2Scorelabel"));
        opponent2Scorelabel->setMinimumSize(QSize(50, 40));

        opponentFormLayout->setWidget(2, QFormLayout::FieldRole, opponent2Scorelabel);

        opponentScoreLabel = new QLabel(formLayoutWidget);
        opponentScoreLabel->setObjectName(QStringLiteral("opponentScoreLabel"));
        opponentScoreLabel->setMinimumSize(QSize(50, 40));

        opponentFormLayout->setWidget(0, QFormLayout::FieldRole, opponentScoreLabel);

        layoutWidget = new QWidget(GameWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 190, 641, 220));
        optionVerticalLayout = new QVBoxLayout(layoutWidget);
        optionVerticalLayout->setObjectName(QStringLiteral("optionVerticalLayout"));
        optionVerticalLayout->setContentsMargins(0, 0, 0, 0);
        option1PushButton = new QPushButton(layoutWidget);
        option1PushButton->setObjectName(QStringLiteral("option1PushButton"));
        option1PushButton->setMinimumSize(QSize(0, 50));

        optionVerticalLayout->addWidget(option1PushButton);

        option2PushButton = new QPushButton(layoutWidget);
        option2PushButton->setObjectName(QStringLiteral("option2PushButton"));
        option2PushButton->setMinimumSize(QSize(0, 50));

        optionVerticalLayout->addWidget(option2PushButton);

        option3PushButton = new QPushButton(layoutWidget);
        option3PushButton->setObjectName(QStringLiteral("option3PushButton"));
        option3PushButton->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setKerning(true);
        option3PushButton->setFont(font);

        optionVerticalLayout->addWidget(option3PushButton);

        option4PushButton = new QPushButton(layoutWidget);
        option4PushButton->setObjectName(QStringLiteral("option4PushButton"));
        option4PushButton->setMinimumSize(QSize(0, 50));

        optionVerticalLayout->addWidget(option4PushButton);

        timerLabel = new QLabel(GameWindow);
        timerLabel->setObjectName(QStringLiteral("timerLabel"));
        timerLabel->setGeometry(QRect(750, 10, 101, 91));
        timerLabel->setStyleSheet(QLatin1String("border-color: rgb(32, 74, 135);\n"
"font: 44pt \"Ubuntu\";\n"
"color: rgb(239, 41, 41);"));
        questionLabel = new QLabel(GameWindow);
        questionLabel->setObjectName(QStringLiteral("questionLabel"));
        questionLabel->setGeometry(QRect(10, 10, 681, 141));
        widget = new QWidget(GameWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(730, 110, 142, 42));
        scoreHorizontalLayout = new QHBoxLayout(widget);
        scoreHorizontalLayout->setObjectName(QStringLiteral("scoreHorizontalLayout"));
        scoreHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        scoreStaticLabel = new QLabel(widget);
        scoreStaticLabel->setObjectName(QStringLiteral("scoreStaticLabel"));
        scoreStaticLabel->setMinimumSize(QSize(0, 40));

        scoreHorizontalLayout->addWidget(scoreStaticLabel);

        scoreLabel = new QLabel(widget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setMinimumSize(QSize(0, 40));

        scoreHorizontalLayout->addWidget(scoreLabel);


        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QDialog *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Dialog", Q_NULLPTR));
        utilityLabel->setText(QString());
        opponenet1NameLabel->setText(QString());
        opponent2NameLabel->setText(QString());
        opponent3NameLabel->setText(QString());
        opponentLabel->setText(QApplication::translate("GameWindow", "Opponents", Q_NULLPTR));
        opponent1Scorelabel->setText(QString());
        opponent3Scorelabel->setText(QString());
        opponent2Scorelabel->setText(QString());
        opponentScoreLabel->setText(QApplication::translate("GameWindow", "Score", Q_NULLPTR));
        option1PushButton->setText(QString());
        option2PushButton->setText(QString());
        option3PushButton->setText(QString());
        option4PushButton->setText(QString());
        timerLabel->setText(QApplication::translate("GameWindow", "df", Q_NULLPTR));
        questionLabel->setText(QString());
        scoreStaticLabel->setText(QApplication::translate("GameWindow", "Score ", Q_NULLPTR));
        scoreLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
