#include "maindialog.h"
#include "ui_maindialog.h"
#include "createroom.h"
#include "QMessageBox"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::setDlgInfo(QString name, int id, int txID)
{
    ui->lb_name->setText(name);
    ui->lb_ID->setText(QString("%1").arg(id));
    QString path = QCoreApplication::applicationDirPath()+"/tx/"+QString("%1.png").arg(txID);
    ui->lb_tx->setPixmap(QPixmap(path));
}

//右键添加菜单
//With Qt::CustomContextMenu,
//the signal customContextMenuRequested() is emitted
//点击出现好友列表
void MainDialog::on_pb_friendlist_clicked()
{
    //发送信号
    Q_EMIT SIG_clickFirendList();
}


void MainDialog::on_pb_create_room_clicked()
{
    //创建房间
    //可选项 人数 密码
    // 6——2狼 2平民 1预言家 1守卫
    // 7——1狼 1白狼王 1民 1预言家 1猎人 1守卫
    // 9——3狼 3民 1预言家 1猎人 1守卫
    Q_EMIT SIG_createRoom();
}





void MainDialog::on_pb_search_room_clicked()
{
    Q_EMIT SIG_addRoom();
}


void MainDialog::on_pb_six_clicked()
{
    //获取房间列表 并显示
    Q_EMIT SIG_getRoomList(6);
}

void MainDialog::on_pb_seven_clicked()
{
    Q_EMIT SIG_getRoomList(7);
}

void MainDialog::on_pb_nine_clicked()
{
    Q_EMIT SIG_getRoomList(9);
}

