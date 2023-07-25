#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowTitle( "登录&注册" );
    setWindowFlags(Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
#include<QRegExp>
void LoginDialog::on_pb_commit_register_clicked()
{
    //获取文本
    QString tel = ui->le_tel_register->text();
    QString pwd = ui->le_pwd_register->text();
    QString confirm = ui->le_confirm_register->text();
    QString name = ui->le_name_register->text();
    //校验合法性
    //不为空
    if(tel.isEmpty() || pwd.isEmpty() || confirm.isEmpty() || name.isEmpty()){
        QMessageBox::about( this, "注册提示", "输入内容不能为空");
        return;
    }
    //电话
    QRegExp exp(QString("^1[356789][0-9]\{9\}$"));
    int ret = exp.exactMatch(tel);
    if(!ret){
        QMessageBox::about( this, "注册提示", "输入电话号格式错误");
        return;
    }
    //密码
    if(pwd.length()>20){
        QMessageBox::about( this, "注册提示", "输入密码过长");
        return;
    }
    if(pwd != confirm){
        QMessageBox::about( this, "注册提示", "输入密码不一致");
        return;
    }
    //昵称
    if(name.length()>10){
        QMessageBox::about( this, "注册提示", "输入昵称过长");
        return;
    }
    //信号发送数据
    Q_EMIT SIG_registerCommit( tel, pwd, name );
}

void LoginDialog::on_pb_commit_clicked()
{
    //获取文本
    QString tel = ui->le_tel->text();
    QString pwd = ui->le_pwd->text();
    //校验合法性
    //不为空
    if( tel.isEmpty() || pwd.isEmpty() ){
        QMessageBox::about( this, "登录提示", "输入内容不能为空");
        return;
    }
    //电话
    QRegExp exp(QString("^1[356789][0-9]\{9\}$"));
    int ret = exp.exactMatch(tel);
    if(!ret){
        QMessageBox::about( this, "登录提示", "输入电话号格式错误");
        return;
    }
    //密码
    if(pwd.length()>20){
        QMessageBox::about( this, "登录提示", "输入密码过长");
        return;
    }
    //信号发送数据
    Q_EMIT SIG_loginCommit( tel, pwd );
}

void LoginDialog::on_pb_clear_register_clicked()
{
    //清空
    ui->le_tel_register->clear();
    ui->le_pwd_register->clear();
    ui->le_confirm_register->clear();
    ui->le_name_register->clear();
}

void LoginDialog::on_pb_clear_clicked()
{
    ui->le_tel_register->clear();
    ui->le_pwd_register->clear();
}



#include <QMessageBox>
void LoginDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this, "退出提示", "是否退出？")
            == QMessageBox::Yes){
        Q_EMIT SIG_close();//执行事件
        event->accept();
    }else{
        event->ignore();//忽略事件
    }
}

