#ifndef ADDROOM_H
#define ADDROOM_H

#include <QWidget>

namespace Ui {
class AddRoom;
}

class AddRoom : public QWidget
{
    Q_OBJECT

public:
    explicit AddRoom(QWidget *parent = nullptr);
    ~AddRoom();
signals:
    void SIG_addRoomInfo(QString roomID, QString pwd);
private slots:
    void on_pb_confirm_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::AddRoom *ui;
};

#endif // ADDROOM_H
