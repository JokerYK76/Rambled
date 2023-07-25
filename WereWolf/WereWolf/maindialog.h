#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();
public:
    void setDlgInfo(QString name, int id, int txID);
signals:
    void SIG_clickFirendList();
    void SIG_createRoom();
    void SIG_addRoom();
    void SIG_getRoomList(int num);
private slots:
    void on_pb_friendlist_clicked();

    void on_pb_create_room_clicked();

    void on_pb_search_room_clicked();

    void on_pb_six_clicked();

    void on_pb_seven_clicked();

    void on_pb_nine_clicked();

private:
    Ui::MainDialog *ui;
};
#endif // MAINDIALOG_H
