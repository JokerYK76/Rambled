#include "gameroomdialog.h"
#include "ui_gameroomdialog.h"
#include <QTime>
#include "algorithm"

GameRoomDialog::GameRoomDialog(QWidget *parent) :
    QDialog(parent), isSuicide(false), hasUsePoinson(false), hasUseSave(false), isAlive(true),
    m_isNight(true), ui(new Ui::GameRoomDialog), lastGuard(0), isOpenAudioDev(false)
{
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    nightTimer = new QTimer(this);
    dayTimer = new QTimer(this);
    connect(nightTimer, SIGNAL(timeout()), this, SLOT(slot_nightOver()));
    connect(dayTimer, SIGNAL(timeout()), this, SLOT(on_pb_stop_clicked()));

    memset(seatShow, 0, sizeof(seatShow));
    buttons[0] = ui->pb_left1;
    buttons[1] = ui->pb_left2;
    buttons[2] = ui->pb_left3;
    buttons[3] = ui->pb_left4;
    buttons[4] = ui->pb_left5;
    buttons[5] = ui->pb_left6;
    buttons[6] =  ui->pb_right1;;
    buttons[7] =  ui->pb_right2;;
    buttons[8] =  ui->pb_right3;;
    buttons[9] =  ui->pb_right4;;
    buttons[10] = ui->pb_right5;;
    buttons[11] = ui->pb_right6;;
    ui->pb_cancel->hide();
    ui->pb_left1->hide();
    ui->pb_left2->hide();
    ui->pb_left3->hide();
    ui->pb_left4->hide();
    ui->pb_left5->hide();
    ui->pb_left6->hide();

    ui->pb_right1->hide();
    ui->pb_right2->hide();
    ui->pb_right3->hide();
    ui->pb_right4->hide();
    ui->pb_right5->hide();
    ui->pb_right6->hide();

    ui->pb_save->hide();
    ui->pb_poison->hide();
    ui->pb_suicide->hide();

    ui->lb_round->hide();
    ui->lb_role->hide();

//    ui->pb_say->hide();
//    ui->pb_stop->hide();

}

GameRoomDialog::~GameRoomDialog()
{
//    SIG_leaveRoom(m_roomID, m_pos);
//    this->hide();
    delete ui;
}


void GameRoomDialog::setDlgInfo(int num, char* roomID, int tx, int pos, std::string pwd)
{
    m_roomID = roomID;
    m_pos = pos;
    this->hide();
    playerNums = num;
//    ui->lb_myID->setText(1);
    ui->lb_roomID->setText(QString("%1人房 房间号:%2 密码:%3").arg(num).arg(roomID).arg(QString::fromStdString(pwd)));
    setSeatImg(pos, tx);
//    QString path = QCoreApplication::applicationDirPath() + "/tx/" + QString("%1.png").arg(tx);
////    ui->lb_left1->setPixmap(path);
//    if(pos <= 6){
//        setLeftPos(pos);
//    }else{
//        setRightPos(pos-6);
//    }
    if(m_role == _ROLE_PROPHET)//预言家不显示自己
        closeSeatPushButton(m_pos);
//    seatShow[m_pos] = 1;//自己的不显示
    this->show();
}

void GameRoomDialog::setSeatImg(int pos, int tx)
{
    QString path = QCoreApplication::applicationDirPath() + "/tx/" + QString("%1.png").arg(tx);
//    ui->lb_left1->setPixmap(path);
    switch (pos) {
    case 1:
        ui->lb_left1->setPixmap(path);
        break;
    case 2:
        ui->lb_left2->setPixmap(path);
        break;
    case 3:
        ui->lb_left3->setPixmap(path);
        break;
    case 4:
        ui->lb_left4->setPixmap(path);
        break;
    case 5:
        ui->lb_left5->setPixmap(path);
        break;
    case 6:
        ui->lb_left6->setPixmap(path);
        break;
    case 7:
        ui->lb_right1->setPixmap(path);
        break;
    case 8:
        ui->lb_right2->setPixmap(path);
        break;
    case 9:
        ui->lb_right3->setPixmap(path);
        break;
    case 10:
        ui->lb_right4->setPixmap(path);
        break;
    case 11:
        ui->lb_right5->setPixmap(path);
        break;
    case 12:
        ui->lb_right6->setPixmap(path);
        break;
    default:
        break;
    }
}

void GameRoomDialog::delSeatImg(int pos)
{
    switch (pos) {
    case 1:
        ui->lb_left1->clear();
        break;
    case 2:
        ui->lb_left2->clear();
        break;
    case 3:
        ui->lb_left3->clear();
        break;
    case 4:
        ui->lb_left4->clear();
        break;
    case 5:
        ui->lb_left5->clear();
        break;
    case 6:
        ui->lb_left6->clear();
        break;
    case 7:
        ui->lb_right1->clear();
        break;
    case 8:
        ui->lb_right2->clear();
        break;
    case 9:
        ui->lb_right3->clear();
        break;
    case 10:
        ui->lb_right4->clear();
        break;
    case 11:
        ui->lb_right5->clear();
        break;
    case 12:
        ui->lb_right6->clear();
        break;
    default:
        break;
    }

}

void GameRoomDialog::setMyID(int id)
{
    ui->lb_myID->setText(QString("%1号").arg(id));
}

void GameRoomDialog::changePromtLabel(std::string content)
{
    ui->lb_round->setText(QString::fromStdString(content));
    ui->lb_round->show();
}

void GameRoomDialog::startGame()
{
    ui->pb_say->hide();
    ui->pb_stop->hide();
    //隐藏准备、开始、邀请按钮
    ui->pb_cancel->hide();
    ui->pb_ready->hide();
    ui->pb_invite->hide();
    changePromtLabel("游戏即将开始，等待分配身份");
}

void GameRoomDialog::setRoleLabel(int roleType)
{
    m_role = roleType;
    ui->lb_role->setText(QString("身份:%1").arg(ROLE[m_role-1]));
    changePromtLabel("身份分发完毕，游戏现在开始");
    ui->lb_role->show();
}

void GameRoomDialog::setRoundLabel(int round, bool isNight, int roleType)
{
    m_isNight = isNight;
    if(isNight){
        ui->pb_say->hide();
        ui->pb_stop->hide();
//        if(isAlive && roleType == m_role)
//            nightTimer->start(_DEF_TIME_NIGHT*1000);
        if(roleType != m_role){
            hideAlivePushButton();
        }
        if(roleType == _ROLE_WOLF){
            if(m_role == _ROLE_GUARD){
                ui->lb_round->setText(QString("第%1夜 守卫环节").arg(round));
                //守卫行动
            }else{
                ui->lb_round->setText(QString("第%1夜 狼人环节").arg(round));
                //狼人行动
            }

            if(m_role == _ROLE_GUARD){
                showAlivePushButton();
            }
            if(m_role == _ROLE_WOLF){
                showAlivePushButton();
                ui->pb_say->show();
                ui->pb_stop->show();
            }
        }else if(roleType == _ROLE_WITCH){
            ui->lb_round->setText(QString("第%1夜 女巫环节").arg(round));
            if(m_role == _ROLE_WITCH){
                if(!isAlive) return;
                if(!hasUseSave)
                    ui->pb_save->show();
                if(!hasUsePoinson)
                    ui->pb_poison->show();
            }
        }else if(roleType == _ROLE_PROPHET){
            ui->lb_round->setText(QString("第%1夜 预言家环节").arg(round));
            if(m_role == _ROLE_PROPHET){
                showAlivePushButton();
            }
        }
    }else{
        //白天显示发言回合
        if(roleType == _ROUND_VOTE){
            //投票环节
            ui->pb_say->hide();
            ui->pb_stop->hide();
            ui->lb_round->setText("投票环节");
            if(isAlive)
                showAlivePushButton();
        }else{
//            hideAlivePushButton();
            ui->lb_round->setText(QString("第%1天 %2号发言环节").arg(round).arg(roleType));
            if(m_pos == roleType){
                dayTimer->start(_DEF_TIME_DAY*1000);
                ui->pb_say->show();
                ui->pb_stop->show();
            }else{
                ui->pb_say->hide();
                ui->pb_stop->hide();
            }
            if(m_role == _ROLE_WOLF || m_role == _ROLE_WOLF_KING_WHITE && isAlive){
                ui->pb_suicide->show();
            }
        }
    }
}

void GameRoomDialog::setDiedInfo(int cause, int first, int second)
{
    //隐藏按键
    hideAlivePushButton();
    //显示
    if(cause == _ANSWER_KILL){
        if(first == 0 && second == 0){
            //聊天框显示
            ui->tb_chat->append(QString("【系统通知】昨晚是平安夜，无人死亡"));
        }
        if(first == 0 && second != 0){
            ui->tb_chat->append(QString("【系统通知】昨晚%1号死亡").arg(second));
            closeSeatPushButton(second-1);
        }
        if(first != 0 && second == 0){
            ui->tb_chat->append(QString("【系统通知】昨晚%1号死亡").arg(first));
            closeSeatPushButton(first-1);
        }
        if(first != 0 && second != 0){
            ui->tb_chat->append(QString("【系统通知】昨晚%1号和%2号死亡").arg(std::min(first,second)).arg(std::max(first,second)));
            closeSeatPushButton(first-1);
            closeSeatPushButton(second-1);
        }
        ui->lb_round->setText("开始发言环节");
    }else{
        //聊天框显示
        if(first == 0)
            ui->tb_chat->append(QString("【系统通知】投票结果，无人放逐"));
        else{
            ui->tb_chat->append(QString("【系统通知】投票结果，%1号放逐").arg(first));
            closeSeatPushButton(first-1);
        }
    }
    if(first == m_pos || second == m_pos){
        isAlive = false;
    }
}

void GameRoomDialog::showAlivePushButton()
{
    if(!isAlive) return;
    if(m_isNight){
        nightTimer->start(_DEF_TIME_NIGHT*1000);
        //晚上 未行动过的显示 0未动 活 1死   2禁止活动
        for(int i=0; i<playerNums; ++i){
            if(seatShow[i] != 1 &&seatShow[i] != 2){
                if(m_role == _ROLE_GUARD && lastGuard == i-1){
                    continue;
                }
                buttons[i]->show();
            }
        }
    }
    else{
        //白天除了死了都得显示
        dayTimer->start(_DEF_TIME_DAY*1000);
        for(int i=0; i<playerNums; ++i){
            if(seatShow[i] != 1){
//                if(m_role == _ROLE_GUARD && lastGuard == i-1){
//                    continue;
//                }
                buttons[i]->show();
            }
        }
    }
}

void GameRoomDialog::showBehavePushButton()
{

}

void GameRoomDialog::hideAlivePushButton()
{
    if(!isAlive) return;
    for(int i=0; i<playerNums; ++i){
        buttons[i]->hide();
    }
}

void GameRoomDialog::closeSeatPushButton(int pos, int type)
{
    seatShow[pos] = type;
}

void GameRoomDialog::clear()
{
    m_role = 0;
    m_isNight = false;
    memset(seatShow, 0, sizeof(seatShow));

    isOpenAudioDev = false;

    //守卫专属
    lastGuard = 0;
    //女巫专属
    hasUsePoinson = true;
    hasUseSave = true;
    //狼人专属
    whoKill = 0;
    isSuicide = false;//白狼王
    isAlive = true;
}

void GameRoomDialog::closeEvent(QCloseEvent * event)
{
    event->ignore();
    SIG_leaveRoom(m_roomID, m_pos);
    this->hide();
}

void GameRoomDialog::slot_addChatMsg(QString body, QString content)
{
    // append 换行追加
    ui->tb_chat->append(QString("【%1】%2").arg(body).arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
}

void GameRoomDialog::slot_nightOver()
{
    SIG_closeAudioDev();
    Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 0);
    isOpenAudioDev = false;
}

void GameRoomDialog::slot_dayOver()
{
    SIG_closeAudioDev();
    if(m_role == _ROLE_GUARD)
        lastGuard = 0;
    Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_role, 0);
    isOpenAudioDev = false;
}

void GameRoomDialog::on_pb_leave_clicked()
{
    //离开
    Q_EMIT SIG_leaveRoom(m_roomID, m_pos);
    this->hide();
}


void GameRoomDialog::on_pb_send_clicked()
{
    // 1、取出编辑栏数据
    // toPlainText取的是不带格式的纯文本
    QString content = ui->te_chat->toPlainText();
    if(content.isEmpty()){
        return;
    }
    // 2、清空编辑栏
    ui->te_chat->clear();

//    // 3、聊天区显示
//    slot_addChatMsg(QString("我"), content);
    // 4、发送聊天数据
    Q_EMIT SIG_sendRoomChatMsg(m_roomID, m_pos, content);
}


void GameRoomDialog::on_pb_ready_clicked()
{
    ui->pb_ready->hide();
    ui->pb_cancel->show();
    //准备
    Q_EMIT SIG_readyGame(m_pos, m_roomID);
}


void GameRoomDialog::on_pb_cancel_clicked()
{
    ui->pb_cancel->hide();
    ui->pb_ready->show();
    //取消掉准备
    Q_EMIT SIG_cancelReadyGame(m_pos, m_roomID);
}


void GameRoomDialog::on_pb_poison_clicked()
{
    //显示do按钮， 进入毒杀模式
    showAlivePushButton();
}


void GameRoomDialog::on_pb_left1_clicked()
{
//    //操作1号
//    STRU_BEHAVIOR rq;
//    rq.roomID = m_roomID;
//    rq.roleType = m_role;
//    rq.who = 1;
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 1;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 1);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 1);
//        if(dayTimer->isActive()){
//            dayTimer->stop();
//        }
    }
//    if(m_role == _ROLE_WOLF){
//        //杀
//        STRU_BEHAVIOR rq;
//        rq.roomID = m_roomID;
//        rq.roleType = m_role;
//    }else if(m_role == _ROLE_WOLF_KING_WHITE && isSuicide){
//        //自爆杀

//    }else if(m_role == _ROLE_GUARD){
//        //守卫
//    }else if(m_role == _ROLE_WITCH){
//        //女巫 毒
//    }else if(m_role == _ROLE_PROPHET){
//        //预言家
//    }else if(m_role == _ROLE_HUNTER){
//        //猎人
//    }
}


void GameRoomDialog::on_pb_left2_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 2;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 2);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 2);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_left3_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 3;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 3);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 3);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_left4_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 4;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 4);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 4);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_left5_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 5;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 5);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 5);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_left6_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 6;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 6);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 6);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_right1_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 7;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 7);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 7);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_right2_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 8;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 8);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 8);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_right3_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 9;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 9);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 9);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_right4_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 10;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 10);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 10);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_right5_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 11;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 11);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 11);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_right6_clicked()
{
    if(m_isNight){
        if(m_role == _ROLE_GUARD)
            lastGuard = 12;
        Q_EMIT SIG_nightOver(atoi(m_roomID.c_str()), m_role, 12);
        if(nightTimer->isActive()){
            nightTimer->stop();
        }
    }
    else{
        Q_EMIT SIG_dayOver(atoi(m_roomID.c_str()), m_pos, 12);
        if(dayTimer->isActive()){
            dayTimer->stop();
        }
    }
}


void GameRoomDialog::on_pb_suicide_clicked()
{
    //白狼王 显示按钮
}


void GameRoomDialog::on_pb_stop_clicked()
{
    SIG_closeAudioDev();
    isOpenAudioDev = false;
    Q_EMIT SIG_overRound(atoi(m_roomID.c_str()), m_pos);
}


void GameRoomDialog::on_pb_say_clicked()
{
    isOpenAudioDev = true;
    Q_EMIT SIG_openAudioDev();
}

