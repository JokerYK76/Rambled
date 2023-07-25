#ifndef GAMEROOMDIALOG_H
#define GAMEROOMDIALOG_H

#include <QDialog>
#include "packdef.h"
#include <QCloseEvent>
#include <QPushButton>
#include <QTimer>
//#include "roomlist.h"

namespace Ui {
class GameRoomDialog;
}


class GameRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameRoomDialog(QWidget *parent = nullptr);
    ~GameRoomDialog();

signals:
    void SIG_leaveRoom(std::string roomID, int pos);
    void SIG_sendRoomChatMsg(std::string roomID, int pos, QString content);
    void SIG_readyGame(int pos, std::string roomID);
    void SIG_cancelReadyGame(int pos, std::string roomID);
    //回合控制
    void SIG_nightOver(int roomID, int roleType, int id);
    void SIG_dayOver(int roomID, int roleType, int id);
    void SIG_overRound(int roomID, int pos);

    //音频
    void SIG_openAudioDev();
    void SIG_closeAudioDev();
public:
    void setDlgInfo(int num, char* roomID, int tx, int pos, std::string pwd);
    void setSeatImg(int pos, int tx);
    void delSeatImg(int pos);
    void setMyID(int id);
    void changePromtLabel(std::string content);
    void startGame();
    void setRoleLabel(int roleType);
    void setRoundLabel(int round, bool isNight, int roleType);
    void setDiedInfo(int cause, int first, int second);
    void showAlivePushButton();
    void showBehavePushButton();
    void hideAlivePushButton();
    void closeSeatPushButton(int pos, int type = 1);
    void clear();
private:
    void closeEvent(QCloseEvent *);
public slots:
    void slot_addChatMsg(QString body, QString content);
    void slot_nightOver();
    void slot_dayOver();
private slots:
    void on_pb_leave_clicked();

    void on_pb_send_clicked();

    void on_pb_ready_clicked();

    void on_pb_cancel_clicked();

    void on_pb_poison_clicked();

    void on_pb_left1_clicked();

    void on_pb_left2_clicked();

    void on_pb_left3_clicked();

    void on_pb_left4_clicked();

    void on_pb_left5_clicked();

    void on_pb_left6_clicked();

    void on_pb_right1_clicked();

    void on_pb_right2_clicked();

    void on_pb_right3_clicked();

    void on_pb_right4_clicked();

    void on_pb_right5_clicked();

    void on_pb_right6_clicked();

    void on_pb_suicide_clicked();

    void on_pb_stop_clicked();

    void on_pb_say_clicked();

private:

    QString ROLE[_ROLE_TYPE_NUMS] = { "平民", "预言家", "女巫", "守卫", "猎人", "狼人", "白狼王" };

    Ui::GameRoomDialog *ui;
    std::string m_roomID;
    int m_pos;
    int m_role;
    int playerNums;
    bool m_isNight;
    int seatShow[12];
    QWidget *buttons[12];

    bool isOpenAudioDev;

    //守卫专属
    int lastGuard;
    //女巫专属
    bool hasUsePoinson;
    bool hasUseSave;
    //狼人专属
    int whoKill;
    bool isSuicide;//白狼王
    bool isAlive;
    QTimer *nightTimer;
    QTimer *dayTimer;
};

#endif // GAMEROOMDIALOG_H
