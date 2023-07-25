#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QWidget>

namespace Ui {
class CreateRoom;
}

class CreateRoom : public QWidget
{
    Q_OBJECT

public:
    explicit CreateRoom(QWidget *parent = nullptr);
    ~CreateRoom();
signals:
    void SIG_createRoomInfo(int num, bool hasPwd, QString pwd);
private slots:
    void on_pb_create_clicked();

    void on_pb_cancel_clicked();

    void on_cb_six_stateChanged(int arg1);

    void on_cb_seven_stateChanged(int arg1);

    void on_cb_night_stateChanged(int arg1);

    void on_cb_has_pwd_stateChanged(int arg1);

    void on_cb_no_pwd_stateChanged(int arg1);

private:
    Ui::CreateRoom *ui;
};

#endif // CREATEROOM_H
