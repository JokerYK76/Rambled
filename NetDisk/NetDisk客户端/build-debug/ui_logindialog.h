/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *lb_icon;
    QTabWidget *tabWidget;
    QWidget *tb_login;
    QLineEdit *le_tel;
    QLabel *lb_tel;
    QLabel *lb_pwd;
    QLineEdit *le_pwd;
    QPushButton *pb_clear;
    QPushButton *pb_commit;
    QWidget *tab_register;
    QLineEdit *le_pwd_register;
    QLabel *lb_tel_register;
    QPushButton *pb_commit_register;
    QLineEdit *le_tel_register;
    QLabel *lb_pwd_register;
    QPushButton *pb_clear_register;
    QLineEdit *le_confirm_register;
    QLabel *lb_confirm_register;
    QLineEdit *le_name_register;
    QLabel *lb_name_register;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(748, 338);
        LoginDialog->setMinimumSize(QSize(748, 338));
        LoginDialog->setMaximumSize(QSize(748, 338));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        LoginDialog->setFont(font);
        lb_icon = new QLabel(LoginDialog);
        lb_icon->setObjectName(QString::fromUtf8("lb_icon"));
        lb_icon->setGeometry(QRect(0, 0, 370, 338));
        lb_icon->setPixmap(QPixmap(QString::fromUtf8(":/tb/mimi.png")));
        lb_icon->setScaledContents(true);
        tabWidget = new QTabWidget(LoginDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(394, 19, 311, 301));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tb_login = new QWidget();
        tb_login->setObjectName(QString::fromUtf8("tb_login"));
        le_tel = new QLineEdit(tb_login);
        le_tel->setObjectName(QString::fromUtf8("le_tel"));
        le_tel->setGeometry(QRect(130, 40, 171, 30));
        le_tel->setClearButtonEnabled(true);
        lb_tel = new QLabel(tb_login);
        lb_tel->setObjectName(QString::fromUtf8("lb_tel"));
        lb_tel->setGeometry(QRect(20, 40, 72, 30));
        lb_pwd = new QLabel(tb_login);
        lb_pwd->setObjectName(QString::fromUtf8("lb_pwd"));
        lb_pwd->setGeometry(QRect(20, 90, 72, 30));
        le_pwd = new QLineEdit(tb_login);
        le_pwd->setObjectName(QString::fromUtf8("le_pwd"));
        le_pwd->setGeometry(QRect(130, 90, 171, 30));
        le_pwd->setEchoMode(QLineEdit::Password);
        le_pwd->setClearButtonEnabled(true);
        pb_clear = new QPushButton(tb_login);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(90, 220, 93, 28));
        pb_commit = new QPushButton(tb_login);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(190, 220, 93, 28));
        tabWidget->addTab(tb_login, QString());
        tab_register = new QWidget();
        tab_register->setObjectName(QString::fromUtf8("tab_register"));
        le_pwd_register = new QLineEdit(tab_register);
        le_pwd_register->setObjectName(QString::fromUtf8("le_pwd_register"));
        le_pwd_register->setGeometry(QRect(130, 90, 171, 30));
        le_pwd_register->setEchoMode(QLineEdit::Password);
        le_pwd_register->setClearButtonEnabled(true);
        lb_tel_register = new QLabel(tab_register);
        lb_tel_register->setObjectName(QString::fromUtf8("lb_tel_register"));
        lb_tel_register->setGeometry(QRect(20, 40, 72, 30));
        pb_commit_register = new QPushButton(tab_register);
        pb_commit_register->setObjectName(QString::fromUtf8("pb_commit_register"));
        pb_commit_register->setGeometry(QRect(190, 220, 93, 28));
        le_tel_register = new QLineEdit(tab_register);
        le_tel_register->setObjectName(QString::fromUtf8("le_tel_register"));
        le_tel_register->setGeometry(QRect(130, 40, 171, 30));
        le_tel_register->setClearButtonEnabled(true);
        lb_pwd_register = new QLabel(tab_register);
        lb_pwd_register->setObjectName(QString::fromUtf8("lb_pwd_register"));
        lb_pwd_register->setGeometry(QRect(20, 90, 72, 30));
        pb_clear_register = new QPushButton(tab_register);
        pb_clear_register->setObjectName(QString::fromUtf8("pb_clear_register"));
        pb_clear_register->setGeometry(QRect(90, 220, 93, 28));
        le_confirm_register = new QLineEdit(tab_register);
        le_confirm_register->setObjectName(QString::fromUtf8("le_confirm_register"));
        le_confirm_register->setGeometry(QRect(130, 140, 171, 30));
        le_confirm_register->setEchoMode(QLineEdit::Password);
        le_confirm_register->setClearButtonEnabled(true);
        lb_confirm_register = new QLabel(tab_register);
        lb_confirm_register->setObjectName(QString::fromUtf8("lb_confirm_register"));
        lb_confirm_register->setGeometry(QRect(20, 140, 72, 30));
        le_name_register = new QLineEdit(tab_register);
        le_name_register->setObjectName(QString::fromUtf8("le_name_register"));
        le_name_register->setGeometry(QRect(130, 180, 171, 30));
        le_name_register->setClearButtonEnabled(true);
        lb_name_register = new QLabel(tab_register);
        lb_name_register->setObjectName(QString::fromUtf8("lb_name_register"));
        lb_name_register->setGeometry(QRect(20, 180, 72, 30));
        tabWidget->addTab(tab_register, QString());
        QWidget::setTabOrder(le_tel_register, le_pwd_register);
        QWidget::setTabOrder(le_pwd_register, le_confirm_register);
        QWidget::setTabOrder(le_confirm_register, le_name_register);
        QWidget::setTabOrder(le_name_register, pb_commit_register);
        QWidget::setTabOrder(pb_commit_register, pb_clear_register);
        QWidget::setTabOrder(pb_clear_register, tabWidget);
        QWidget::setTabOrder(tabWidget, le_tel);
        QWidget::setTabOrder(le_tel, le_pwd);
        QWidget::setTabOrder(le_pwd, pb_commit);
        QWidget::setTabOrder(pb_commit, pb_clear);

        retranslateUi(LoginDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        lb_icon->setText(QString());
        le_tel->setText(QApplication::translate("LoginDialog", "13512345678", nullptr));
        lb_tel->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
        lb_pwd->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        le_pwd->setText(QApplication::translate("LoginDialog", "1", nullptr));
        pb_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        pb_commit->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tb_login), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
#ifndef QT_NO_TOOLTIP
        le_pwd_register->setToolTip(QApplication::translate("LoginDialog", "\350\276\223\345\205\245\351\225\277\345\272\246\344\270\215\350\266\205\350\277\20720\344\275\215", nullptr));
#endif // QT_NO_TOOLTIP
        le_pwd_register->setText(QString());
        lb_tel_register->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
        pb_commit_register->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
#ifndef QT_NO_TOOLTIP
        le_tel_register->setToolTip(QApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\24511\344\275\215\346\225\260\345\255\227", nullptr));
#endif // QT_NO_TOOLTIP
        le_tel_register->setText(QString());
        lb_pwd_register->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        pb_clear_register->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        le_confirm_register->setText(QString());
        lb_confirm_register->setText(QApplication::translate("LoginDialog", "\347\241\256\350\256\244", nullptr));
#ifndef QT_NO_TOOLTIP
        le_name_register->setToolTip(QApplication::translate("LoginDialog", "\350\276\223\345\205\245\351\225\277\345\272\246\344\270\215\350\266\205\350\277\20710\344\275\215", nullptr));
#endif // QT_NO_TOOLTIP
        le_name_register->setText(QString());
        lb_name_register->setText(QApplication::translate("LoginDialog", "\346\230\265\347\247\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_register), QApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
