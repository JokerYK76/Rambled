#ifndef CHATDLG_H
#define CHATDLG_H

#include <QWidget>

namespace Ui {
class ChatDlg;
}

class ChatDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDlg(QWidget *parent = nullptr);
    ~ChatDlg();

    int getUserID() const;

signals:
    void SIG_SendChatMsg(int id, QString content);
public slots:
    void slot_setInfo(int id, QString name);
    void slot_addChatMsg(QString name, QString content);
private slots:
    void on_pb_send_clicked();

private:
    int userID;
    Ui::ChatDlg *ui;
};

#endif // CHATDLG_H
