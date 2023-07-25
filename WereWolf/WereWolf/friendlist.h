#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include "frienditem.h"
#include "packdef.h"

namespace Ui {
class FriendList;
}

class FriendItem;

class FriendList : public QWidget
{
    Q_OBJECT

public:
    explicit FriendList(QWidget *parent = nullptr);
    ~FriendList();
signals:
    void SIG_searchOne(QString tel);
public slots:
    void slot_addItem(FriendItem *item);
    void slot_clear();
//    void slot_addSearchItem(FriendItem *item);
//    void slot_showSearchResult(FriendInfo info);
private slots:
    void on_pb_search_clicked();

private:
    Ui::FriendList *ui;
    QVBoxLayout *m_layout;
};

#endif // FRIENDLIST_H
