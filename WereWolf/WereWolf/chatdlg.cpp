#include "chatdlg.h"
#include "ui_chatdlg.h"
#include <QTime>

ChatDlg::ChatDlg(QWidget *parent) : userID(0),
    QWidget(parent),
    ui(new Ui::ChatDlg)
{
    ui->setupUi(this);
}

ChatDlg::~ChatDlg()
{
    delete ui;
}

void ChatDlg::slot_setInfo(int id, QString name)
{
    userID = id;
    ui->lb_title->setText(QString("与%1的聊天").arg(name));
}

void ChatDlg::slot_addChatMsg(QString name, QString content)
{
    // append 换行追加
    ui->tb_chat->append(QString("【%1】%2").arg(name).arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
}

int ChatDlg::getUserID() const
{
    return userID;
}

void ChatDlg::on_pb_send_clicked()
{
    // 1、取出编辑栏数据
    // toPlainText取的是不带格式的纯文本
    QString content = ui->te_write->toPlainText();
    if(content.isEmpty()){
        return;
    }
    // 2、清空编辑栏
    ui->te_write->clear();

    // 3、聊天区显示
    slot_addChatMsg(QString("我"), content);
    // 4、发送聊天数据
    Q_EMIT SIG_SendChatMsg(userID, content);
}

