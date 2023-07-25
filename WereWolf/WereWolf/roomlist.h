#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>
#include "roomitem.h"

namespace Ui {
class RoomList;
}

class RoomList : public QWidget
{
    Q_OBJECT

public:
    explicit RoomList(QWidget *parent = nullptr);
    ~RoomList();
signals:
    void SIG_refreshRomList(int num);
public:
    void setRoomNum(int num);
    void addRoomItem(RoomItem *item);
    void clear();
private slots:
    void on_pb_refresh_clicked();
private:
    void closeEvent(QCloseEvent *);
private:
    Ui::RoomList *ui;
    QVBoxLayout *m_layout;
    int m_roomNum;//房间人数
};

#endif // ROOMLIST_H
