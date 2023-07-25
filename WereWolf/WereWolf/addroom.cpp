#include "addroom.h"
#include "ui_addroom.h"

AddRoom::AddRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRoom)
{
    ui->setupUi(this);
}

AddRoom::~AddRoom()
{
    delete ui;
}

void AddRoom::on_pb_confirm_clicked()
{
    Q_EMIT SIG_addRoomInfo(ui->le_roomID->text(), ui->le_pwd->text());
    this->hide();
    delete ui;
}


void AddRoom::on_pb_cancel_clicked()
{
    this->hide();
    delete ui;
}

