#include "roomlist.h"
#include "ui_roomlist.h"

RoomList::RoomList(QWidget *parent) :
    QWidget(parent), m_roomNum(0),
    ui(new Ui::RoomList)
{
    ui->setupUi(this);
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(3);
    ui->wdg_roomlist->setLayout(m_layout);
}

RoomList::~RoomList()
{
    delete ui;
}

void RoomList::setRoomNum(int num)
{
    m_roomNum = num;
    ui->lb_roomType->setText(QString("%1人房").arg(num));
}

void RoomList::addRoomItem(RoomItem *item)
{
    m_layout->addWidget(item);
}

void RoomList::clear()
{
    QLayoutItem *delItem;
    while((delItem = m_layout->takeAt(0))){
        delete delItem->widget();
        delete delItem;
    }
}

void RoomList::on_pb_refresh_clicked()
{
    clear();
    Q_EMIT SIG_refreshRomList(m_roomNum);
}

void RoomList::closeEvent(QCloseEvent *)
{
    clear();
}

