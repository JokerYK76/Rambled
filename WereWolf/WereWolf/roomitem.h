#ifndef ROOMITEM_H
#define ROOMITEM_H

#include <QWidget>

namespace Ui {
class RoomItem;
}

class RoomItem : public QWidget
{
    Q_OBJECT

public:
    explicit RoomItem(QWidget *parent = nullptr);
    ~RoomItem();

signals:
    void SIG_addRoom(QString roomID, QString pwd);
public:
    void setInfo(int roomID, bool hasPWD, int curNum, int maxNum);

private slots:

    void on_pb_addRoom_clicked();

private:
    Ui::RoomItem *ui;
    int m_roomID;
    bool m_hasPWD;
};

#endif // ROOMITEM_H
