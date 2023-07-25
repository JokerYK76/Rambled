#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class FriendItem;
}

class FriendItem : public QWidget
{
    Q_OBJECT
signals:
    void SIG_addFriend(int userid);
    void SIG_chatWithOne(int id, QString name);
public slots:
    void slot_setInfo(std::string name, int uid, std::string label ,int txID);
    void slot_dealMenuAddFriend(bool flag);
    void slot_dealMenuChat(bool falg);
    void slot_showMenu(const QPoint pos);
public:
    explicit FriendItem(QWidget *parent = nullptr);
    ~FriendItem();
    void setIsFriend(bool newIsFriend);

private:
    int m_id;
    Ui::FriendItem *ui;
    QString hower_label;
    QMenu m_menu;
    QAction *actAddFriend;
    QAction *actChat;
    bool isFriend;
};

#endif // FRIENDITEM_H
