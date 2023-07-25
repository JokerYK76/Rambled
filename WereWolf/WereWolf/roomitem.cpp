#include "roomitem.h"
#include "ui_roomitem.h"
#include <QInputDialog>

RoomItem::RoomItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomItem)
{
    ui->setupUi(this);
}

RoomItem::~RoomItem()
{
    delete ui;
}

void RoomItem::setInfo(int roomID, bool hasPWD, int curNum, int maxNum)
{
    m_roomID = roomID;
    m_hasPWD = hasPWD;
    ui->lb_roomID->setText(QString("%1").arg(roomID));
    if(hasPWD)
        ui->lb_pwd->setText("有密码");
    else
        ui->lb_pwd->setText("无密码");
    ui->lb_number->setText(QString("%1/%2").arg(curNum).arg(maxNum));
    if(curNum == maxNum)
        ui->pb_addRoom->hide();
}



void RoomItem::on_pb_addRoom_clicked()
{
    QString pwd = "";
    if(m_hasPWD){
        pwd = QInputDialog::getText(this, "输入", "输入密码", QLineEdit::Normal);
        Q_EMIT SIG_addRoom(ui->lb_roomID->text(), pwd);
    }else{
        Q_EMIT SIG_addRoom(ui->lb_roomID->text(), pwd);
    }

}

