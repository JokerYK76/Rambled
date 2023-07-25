#include "frienditem.h"
#include "ui_frienditem.h"
#include "ckernel.h"

void FriendItem::slot_setInfo(std::string name, int uid, std::string label, int txID)
{
    m_id = uid;
    ui->lb_name->setText("昵称:"+QString::fromStdString(name));
    ui->lb_id->setText(QString("ID:%1").arg(uid));
    QString path = QCoreApplication::applicationDirPath() + "/tx/" + QString("%1.png").arg(txID);
    ui->lb_tx->setPixmap(QPixmap(path));
    hower_label = QString::fromStdString(label);

    //设置悬浮显示
    this->setMouseTracking(true);
    this->setToolTip(QString("%1").arg(hower_label));

    //右键菜单
    actAddFriend = new QAction(tr("添加好友"), this);
    connect(actAddFriend, SIGNAL(triggered(bool)),
            this, SLOT(slot_dealMenuAddFriend(bool)));
    actChat = new QAction(tr("聊天"), this);
    connect(actChat, SIGNAL(triggered(bool)),
            this, SLOT(slot_dealMenuChat(bool)));

    this->setContextMenuPolicy(Qt::CustomContextMenu);//添加右键菜单策略
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_showMenu(QPoint)));


}
#include <QDebug>
void FriendItem::slot_dealMenuAddFriend(bool flag)
{
    Q_EMIT SIG_addFriend(m_id);
}

void FriendItem::slot_dealMenuChat(bool falg)
{
    Q_EMIT SIG_chatWithOne(m_id, ui->lb_name->text());
}

void FriendItem::slot_showMenu(const QPoint pos)
{
    m_menu.clear();
    if(!isFriend){
        m_menu.addAction(actAddFriend);
    }
    m_menu.addAction(actChat);
    m_menu.exec(QCursor::pos());  //在当前鼠标处堵住
}


FriendItem::FriendItem(QWidget *parent) : isFriend(false),
    QWidget(parent),
    ui(new Ui::FriendItem)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowTitle("用户信息");
}

FriendItem::~FriendItem()
{
    delete ui;
}

void FriendItem::setIsFriend(bool newIsFriend)
{
    isFriend = newIsFriend;
}

