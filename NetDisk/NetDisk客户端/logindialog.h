#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
signals:
    void SIG_registerCommit( QString tel, QString pwd, QString name );
    void SIG_loginCommit( QString tel, QString pwd );
    void SIG_close();
private slots:
    void on_pb_commit_register_clicked();

    void on_pb_clear_register_clicked();

    void on_pb_commit_clicked();

    void on_pb_clear_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::LoginDialog *ui;

};

#endif // LOGINDIALOG_H
