#include "createroom.h"
#include "ui_createroom.h"
//#include "ckernel.h"

CreateRoom::CreateRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateRoom)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

//    CKernel *tmpKernel = CKernel::getInstance();
//    connect(this, SIGNAL(SIG_createRoomInfo(int,bool,QString)),
//            tmpKernel, SLOT(slot_createRoomInfo(int,bool,QString)));
}

CreateRoom::~CreateRoom()
{
    delete ui;
}

void CreateRoom::on_pb_create_clicked()
{
    //创建房间
    //获取人数
    int num;
    if(ui->cb_six->checkState() == Qt::CheckState::Checked){
        num = 6;
    }
    if(ui->cb_seven->checkState() == Qt::CheckState::Checked){
        num = 7;
    }
    if(ui->cb_night->checkState() == Qt::CheckState::Checked){
        num = 9;
    }
    //获取有无密码
    bool hasPwd;
    QString pwd = ui->le_pwd->text();
    if(ui->cb_has_pwd->checkState() == Qt::CheckState::Checked){
        hasPwd = true;
    }else{
        hasPwd = false;
    }
    //发送信号传递出去
    Q_EMIT SIG_createRoomInfo(num, hasPwd, pwd);
    this->hide();
    delete ui;
}


void CreateRoom::on_pb_cancel_clicked()
{
    this->hide();
    //回收
    delete ui;
}


void CreateRoom::on_cb_six_stateChanged(int arg1)
{
    //6人
    if(arg1 == Qt::CheckState::Checked){
        ui->cb_seven->blockSignals(true);
        ui->cb_seven->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_seven->blockSignals(false);
        ui->cb_night->blockSignals(true);
        ui->cb_night->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_night->blockSignals(false);
    }
}


void CreateRoom::on_cb_seven_stateChanged(int arg1)
{
    //7人
    if(arg1 == Qt::CheckState::Checked){
        ui->cb_six->blockSignals(true);
        ui->cb_six->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_six->blockSignals(false);
        ui->cb_night->blockSignals(true);
        ui->cb_night->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_night->blockSignals(false);
    }
}


void CreateRoom::on_cb_night_stateChanged(int arg1)
{
    //9人
    if(arg1 == Qt::CheckState::Checked){
        ui->cb_seven->blockSignals(true);
        ui->cb_seven->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_seven->blockSignals(false);
        ui->cb_six->blockSignals(true);
        ui->cb_six->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_six->blockSignals(false);
    }
}


void CreateRoom::on_cb_has_pwd_stateChanged(int arg1)
{
    //有密码
    if(arg1 == Qt::CheckState::Checked){
        ui->cb_no_pwd->blockSignals(true);
        ui->cb_no_pwd->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_no_pwd->blockSignals(false);
    }
}


void CreateRoom::on_cb_no_pwd_stateChanged(int arg1)
{
    //无密码
    if(arg1 == Qt::CheckState::Checked){
        ui->cb_has_pwd->blockSignals(true);
        ui->cb_has_pwd->setCheckState(Qt::CheckState::Unchecked);
        ui->cb_has_pwd->blockSignals(false);
    }
}

