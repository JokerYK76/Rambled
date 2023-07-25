#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include "common.h"
#include "mytablewidgetitem.h"
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_close();
    void SIG_downloadFile(int fileid);
    void SIG_uploadFile(QString path);
    void SIG_uploadFolder(QString path);
    void SIG_addFolder( QString name );
    void SIG_changePath( QString path );
    void SIG_deleteFile(QString path, QVector<int> fileidArray);
    void SIG_shareFile(QString path, QVector<int> fileidArray);
    void SIG_getShare(QString path, int link);
    void SIG_setUploadPause(int fileId, int pauseFlag);
    void SIG_setDownloadPause(int fileId, int pauseFlag);

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();
public slots:
    void closeEvent(QCloseEvent* event);
    void on_pb_fillePage_clicked();

    void on_pb_transmitPage_clicked();

    void on_pb_sharePage_clicked();
    void on_tab_file_cellClicked(int row, int column);

    //菜单显示
    void slot_menuShow(QPoint point);
    void slot_menuUploadShow(QPoint point);
    void slot_menuDownloadShow(QPoint point);


    void slot_dealMenu(QAction* act);
    void slot_dealMenuUploadFile(QAction* act);
    void slot_dealMenuDownloadFile(QAction* act);
    void slot_dealMenuAddFile(QAction* act);
    //下载
    void slot_insertDownloadFile(FileInfo& info);
    void slot_insertComplete(FileInfo& info);
    void slot_updateFileProgress(int fileid, int pos);
    //上传
    void slot_insertUploadFile(FileInfo& info);
    void slot_insertUploadComplete(FileInfo& info);
    void slot_updateUploadFileProgress(int fileid, int pos);

    void slot_insertShare(QString name, QString size, QString time, QString link);

    void slot_folderButtonClick();

    FileInfo& slot_getDownloadFileInfoByFileID(int fileid);
    FileInfo& slot_getUploadFileInfoByFileID(int fileid);

public:
    void slot_setInfo(QString name);
    void slot_insertFileInfo(FileInfo& info);

    //清空文件列表
    void deleteFileList();
    void deleteShareList();

private slots:
    void on_pb_addFile_clicked();

    void on_tab_file_cellDoubleClicked(int row, int column);

    void on_pb_preDir_clicked();

    void on_table_upload_cellClicked(int row, int column);

    void on_table_download_cellClicked(int row, int column);

private:
    Ui::MainDialog *ui;
    QMenu m_menu;
    QMenu m_menuAddFile;
    QMenu m_menuUpload;
    QMenu m_menuDownload;
};
#endif // MAINDIALOG_H
