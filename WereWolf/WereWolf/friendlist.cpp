#include "friendlist.h"
#include "ui_friendlist.h"
#include <QMessageBox>

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowTitle("好友列表");

    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(3);
    ui->wdg_list->setLayout(m_layout);

    //测试
//    for(int i=0; i<5;++i){
//        FriendItem* item = new FriendItem;
//        item->slot_setInfo("1", i, "null", 0);
//        this->slot_addItem(item);
//    }
}

FriendList::~FriendList()
{
    delete ui;
}

void FriendList::slot_addItem(FriendItem *item)
{
    item->setIsFriend(true);
    m_layout->addWidget(item);
}

void FriendList::slot_clear()
{
    QLayoutItem *delItem;
    while((delItem = m_layout->takeAt(0))){
        delete delItem->widget();
        delete delItem;
    }
}

//void FriendList::slot_addSearchItem(FriendItem *item)
//{

//}

//void FriendList::slot_showSearchResult(FriendInfo info)
//{
//    FriendItem item;
//    item.slot_setInfo(info.name, info.userid, info.label, info.tx);
//    item.show();
//}


#include <QDebug>
void FriendList::on_pb_search_clicked()
{
    qDebug() << __func__ ;
    QString tel = ui->le_input_id->text();
    if(tel.isEmpty()){
        QMessageBox::about(this, "提示", "id不能为空!");
        return;
    }
    //发送信号请求查询
    Q_EMIT SIG_searchOne(tel);
}

