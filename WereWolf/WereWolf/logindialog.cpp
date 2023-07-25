#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

#include <QDebug>
void LoginDialog::on_pb_login_clicked()
{
    //获取手机号和密码 通过信号发送
    QString tel = ui->le_tel_login->text();
    QString pwd = ui->le_pwd_login->text();

//    //输出一下
//    qDebug() << "tel:" << tel;
//    qDebug() << "pwd:" << pwd;

    //校验格式，合法性

    //发送信号
    Q_EMIT SIG_loginInfo(tel, pwd);
}


void LoginDialog::on_pb_confirm_register_clicked()
{
    //获取注册信息
    QString tel = ui->le_tel_register->text();
    QString pwd = ui->le_pwd_register->text();
    QString againPWD = ui->le_again_register->text();
    QString name = ui->le_name_register->text();

//    //输出一下
//    qDebug() << "tel:" << tel;
//    qDebug() << "pwd:" << pwd;
//    qDebug() << "again pwd:" << againPWD;

    //校验
    //密码一致性校验
    if(pwd != againPWD){
        QMessageBox::about(this, "注册提示", "密码输入不一致");
        return;
    }
    //发送信号
    Q_EMIT SIG_registerInfo(tel, pwd, name);
}


void LoginDialog::on_pb_clear_register_clicked()
{
    ui->le_tel_register->clear();
    ui->le_pwd_register->clear();
    ui->le_again_register->clear();
    ui->le_name_register->clear();
}


void LoginDialog::on_pb_clear_clicked()
{
    ui->le_pwd_login->clear();
    ui->le_tel_login->clear();
}

