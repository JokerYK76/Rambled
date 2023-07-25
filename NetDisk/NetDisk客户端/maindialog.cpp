#include "maindialog.h"
#include "ui_maindialog.h"


MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
   ui->setupUi(this);
   setWindowTitle( "MyNetDisk" );
   setWindowFlags(Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);
   //右键添加菜单
   //With Qt::CustomContextMenu,
   //the signal customContextMenuRequested() is emitted
   ui->tab_file->setContextMenuPolicy(Qt::CustomContextMenu);
   ui->table_upload->setContextMenuPolicy(Qt::CustomContextMenu);
   ui->table_download->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(ui->tab_file, SIGNAL(customContextMenuRequested(QPoint)),
           this, SLOT(slot_menuShow(QPoint)));
   connect(ui->table_upload, SIGNAL(customContextMenuRequested(QPoint)),
           this, SLOT(slot_menuUploadShow(QPoint)));
   connect(ui->table_download, SIGNAL(customContextMenuRequested(QPoint)),
           this, SLOT(slot_menuDownloadShow(QPoint)));

   m_menu.addAction( QIcon(":/images/folder.png"), "新建文件夹");
   m_menu.addAction("下载");
   m_menu.addAction("删除");
   m_menu.addAction("分享");
   m_menu.addAction("收藏");
   m_menu.addAction("获取分享");
   //trigger 触发
   connect(&m_menu, SIGNAL( triggered(QAction*) ),
           this, SLOT( slot_dealMenu(QAction*) ));

   m_menuUpload.addAction("暂停");
   m_menuUpload.addAction("开始");
   connect(&m_menuUpload, SIGNAL( triggered(QAction*) ),
           this, SLOT( slot_dealMenuUploadFile(QAction*) ));

   m_menuDownload.addAction("暂停");
   m_menuDownload.addAction("开始");
   connect(&m_menuDownload, SIGNAL( triggered(QAction*) ),
           this, SLOT( slot_dealMenuDownloadFile(QAction*) ));

   m_menuAddFile.addAction("上传文件");
   m_menuAddFile.addAction("上传文件夹");
   connect(&m_menuAddFile, SIGNAL( triggered(QAction*) ),
           this, SLOT( slot_dealMenuAddFile(QAction*) ));

   ui->sw_right->setCurrentIndex(0);//默认右侧界面显示文件页
   ui->tw_transmit->setCurrentIndex(1);//默认传输界面显示下载页
}

MainDialog::~MainDialog()
{
    delete ui;
}
#include <QMessageBox>
void MainDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this, "退出提示", "是否退出？")
            == QMessageBox::Yes){
        Q_EMIT SIG_close();//执行事件
        event->accept();
    }else{
        event->ignore();//忽略事件
    }
}


void MainDialog::on_pb_fillePage_clicked()
{
    ui->sw_right->setCurrentIndex( 0 );
}


void MainDialog::on_pb_transmitPage_clicked()
{
    ui->sw_right->setCurrentIndex( 1 );
}


void MainDialog::on_pb_sharePage_clicked()
{
    ui->sw_right->setCurrentIndex( 2 );
}

void MainDialog::slot_setInfo(QString name)
{
    ui->pb_user->setText(name);
}

void MainDialog::slot_insertFileInfo(FileInfo &info)
{
    MyTableWidgetItem *item0 = new MyTableWidgetItem;
    item0->setInfo(info);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText( info.time );
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText( FileInfo::getSize(info.size) );

    int row = ui->tab_file->rowCount();
    ui->tab_file->setRowCount( row + 1);
    ui->tab_file->setItem(row, 0, item0);
    ui->tab_file->setItem(row, 1, item1);
    ui->tab_file->setItem(row, 2, item2);
}

void MainDialog::deleteFileList()
{
    int rows = ui->tab_file->rowCount();
    for(int i=rows-1; i>=0; --i){
        ui->tab_file->removeRow(i);
    }
}

void MainDialog::deleteShareList()
{
    int rows = ui->table_share->rowCount();
    for(int i=rows-1; i>=0; --i){
        ui->table_share->removeRow(i);
    }
}
//插入下载列表
#include<QProgressBar>
void MainDialog::slot_insertDownloadFile(FileInfo &info)
{
    MyTableWidgetItem *item0 = new MyTableWidgetItem;
    item0->setInfo(info);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText( info.getSize(info.size) );
    QProgressBar *item2 = new QProgressBar;
    item2->setMaximum(info.size);
    item2->setValue(0);
    QPushButton *pButton = new QPushButton;
    if(info.isPause == 0)
        pButton->setText("暂停");
    else
        pButton->setText("开始");

    int row = ui->table_download->rowCount();
    ui->table_download->setRowCount( row + 1);
    ui->table_download->setItem(row, 0, item0);
    ui->table_download->setItem(row, 1, item1);
    ui->table_download->setCellWidget(row, 2, item2);
    ui->table_download->setCellWidget(row, 3, pButton);
}
//插入下载完成列表
#include <QDateTime>
void MainDialog::slot_insertComplete(FileInfo &info)
{
    MyTableWidgetItem *item0 = new MyTableWidgetItem;
    item0->setInfo(info);
    //大小
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText( info.getSize(info.size) );
    //时间
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm::ss");
    item2->setText( time );
    //按钮
    QPushButton *pButton = new QPushButton;
    pButton->setIcon(QIcon(":/images/folder.png"));
    //tooltip可以显示信息，借此完成信号传递
    pButton->setToolTip(info.absolutePath);
    pButton->setFlat( true );
    connect(pButton, SIGNAL(clicked()),
            this, SLOT(slot_folderButtonClick()));
    int row = ui->table_complete->rowCount();
    ui->table_complete->setRowCount( row + 1);
    ui->table_complete->setItem(row, 0, item0);
    ui->table_complete->setItem(row, 1, item1);
    ui->table_complete->setItem(row, 2, item2);
    ui->table_complete->setCellWidget(row, 3, pButton);
}
#include<QDebug>
void MainDialog::slot_updateFileProgress(int fileid, int pos)
{
    qDebug() << __func__ ;
    //遍历找到对应控件
    int rows = ui->table_download->rowCount();
    for(int i=0; i<rows; ++i){
        MyTableWidgetItem *item = (MyTableWidgetItem*)ui->table_download->item(i, 0);
        if(item->m_info.fileid == fileid){
            item->m_info.pos = pos;
            QProgressBar * progress = (QProgressBar*)ui->table_download->cellWidget(i, 2);
            progress->setValue(pos);

            if(progress->value() >= progress->maximum()){
                //添加已完成列表
                this->slot_insertComplete(item->m_info);
                //删除下载列表
                ui->table_download->removeRow(i);
            }
            return;
        }
    }
}
//上传
void MainDialog::slot_insertUploadFile(FileInfo &info)
{
    MyTableWidgetItem *item0 = new MyTableWidgetItem;
    item0->setInfo(info);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText( info.getSize(info.size) );
    QProgressBar *item2 = new QProgressBar;
    item2->setMaximum(info.size);
    item2->setValue(0);
    QPushButton *pButton = new QPushButton;
    if(info.isPause == 0)
        pButton->setText("暂停");
    else
        pButton->setText("开始");

    int row = ui->table_upload->rowCount();
    ui->table_upload->setRowCount( row + 1);
    ui->table_upload->setItem(row, 0, item0);
    ui->table_upload->setItem(row, 1, item1);
    ui->table_upload->setCellWidget(row, 2, item2);
    ui->table_upload->setCellWidget(row, 3, pButton);
}

void MainDialog::slot_insertUploadComplete(FileInfo &info)
{
    MyTableWidgetItem *item0 = new MyTableWidgetItem;
    item0->setInfo(info);
    //大小
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText( info.getSize(info.size) );
    //时间
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm::ss");
    item2->setText( time );
    //按钮
    QPushButton *pButton = new QPushButton;
    pButton->setIcon(QIcon(":/images/folder.png"));
    pButton->setText("上传完成");
    pButton->setFlat( true );

    int row = ui->table_complete->rowCount();
    ui->table_complete->setRowCount( row + 1);
    ui->table_complete->setItem(row, 0, item0);
    ui->table_complete->setItem(row, 1, item1);
    ui->table_complete->setItem(row, 2, item2);
    ui->table_complete->setCellWidget(row, 3, pButton);
}

void MainDialog::slot_updateUploadFileProgress(int fileid, int pos)
{
    qDebug() << __func__ ;
    //遍历找到对应控件
    int rows = ui->table_upload->rowCount();
    for(int i=0; i<rows; ++i){
        MyTableWidgetItem *item = (MyTableWidgetItem*)ui->table_upload->item(i, 0);
        if(item->m_info.fileid == fileid){
            item->m_info.pos = pos;
            QProgressBar * progress = (QProgressBar*)ui->table_upload->cellWidget(i, 2);
            progress->setValue(pos);

            if(progress->value() >= progress->maximum()){
                //添加已完成列表
                this->slot_insertUploadComplete(item->m_info);
                //删除下载列表
                ui->table_upload->removeRow(i);
            }
            return;
        }
    }
}

void MainDialog::slot_insertShare(QString name, QString size, QString time, QString link)
{
    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setText(name);
    //大小
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText( size );
    //时间
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText( time );
    //link
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText( link );

    int row = ui->table_share->rowCount();
    ui->table_share->setRowCount( row + 1);
    ui->table_share->setItem(row, 0, item0);
    ui->table_share->setItem(row, 1, item1);
    ui->table_share->setItem(row, 2, item2);
    ui->table_share->setItem(row, 3, item3);
}
#include<QProcess>
#include<QString>
void MainDialog::slot_folderButtonClick()
{
    //获取点击的按钮控件——QObject::sender()
    QPushButton* pButton = (QPushButton*)QObject::sender();
    //通过tooltip获取文件夹所在位置
    //cmd不认/要将其改为 \\
    QString filePath = pButton->toolTip().replace('/', '\\');
    //QProcess::startDetached可以使用cmd命令
    QProcess process;
    //explorer /select, D:/NetDisk/filename    /select可以跳转到目标文件路径下，并标记该文件
    process.startDetached("explorer",
                          QStringList()<< QString("/select,")<<pButton->toolTip().replace('/', '\\'));

}

FileInfo& MainDialog::slot_getDownloadFileInfoByFileID(int fileid)
{
    //遍历下载列表
    int rows = ui->table_download->rowCount();
    for(int i=0; i<rows; ++i){
        MyTableWidgetItem *item = (MyTableWidgetItem*)ui->table_download->item(i, 0);
        if(item->m_info.fileid == fileid){
            //找到id所在控件，取第0列数据
            return item->m_info;
        }
    }
}

FileInfo& MainDialog::slot_getUploadFileInfoByFileID(int fileid)
{
    //遍历上传列表
    int rows = ui->table_upload->rowCount();
    for(int i=0; i<rows; ++i){
        MyTableWidgetItem *item = (MyTableWidgetItem*)ui->table_upload->item(i, 0);
        if(item->m_info.fileid == fileid){
            //找到id所在控件，取第0列数据
            return item->m_info;
        }
    }
}

void MainDialog::slot_menuShow(QPoint point)//相对位置
{
    //鼠标绝对位置
    m_menu.exec( QCursor::pos() );
}

void MainDialog::slot_menuUploadShow(QPoint point)
{
    //鼠标绝对位置
    m_menuUpload.exec( QCursor::pos() );
}

void MainDialog::slot_menuDownloadShow(QPoint point)
{
    //鼠标绝对位置
    m_menuDownload.exec( QCursor::pos() );
}
#include<QDebug>
#include<QInputDialog>
void MainDialog::slot_dealMenu(QAction *act)
{
    if(act->text() == "新建文件夹"){
        qDebug() << "新建文件夹";
        //弹窗 获取文件名
        QString name = QInputDialog::getText(this, "新建文件夹", "请输入名称：");
        if(name.isEmpty()) name = "新建文件夹";
        //去重
        int rows = ui->tab_file->rowCount();
        for(int i=0; i<rows; ++i){
            QString tmpName = ui->tab_file->item(i, 0)->text();
            if(name == tmpName){
                QMessageBox::about(this, "提示", "名称不可重复");
                return;
            }
        }
        //过滤 不能全为空格 不能有 / \\ * ? | : < > "
        QString tmp = name;
        if(tmp.remove(" ").isEmpty()){
            QMessageBox::about(this, "提示", "名称不可全为空格");
            return;
        }
        if(name.contains("/") || name.contains("\\") ||
           name.contains("*") || name.contains("?") ||
           name.contains("|") || name.contains(":") ||
           name.contains("<") || name.contains(">") ||
           name.contains("\"")){
            QMessageBox::about(this, "提示", "名称不可含有/ \\ * ? | : < > \"");
            return;
        }
        //发送信号给核心类处理请求
        Q_EMIT SIG_addFolder( name );
    }else if(act->text() == "下载"){
        qDebug() << "下载";
        //发送下载文件请求信号
        //遍历，获取所有打钩控件
        int rows = ui->tab_file->rowCount();
        for(int i=0; i<rows; ++i){
            //获取文件id
            MyTableWidgetItem *item = (MyTableWidgetItem*)ui->tab_file->item(i, 0);
            int fileid;
            //查看是否被勾选
            if(item->checkState() == Qt::Checked){
                //判断是否在下载列表，在则不请求下载
                fileid = item->m_info.fileid;
                //发送信号
                //qDebug() << "fileid="<<fileid;
                Q_EMIT SIG_downloadFile(fileid);
            }

        }

    }else if(act->text() == "删除"){
        qDebug() << "删除";
        QVector<int> fileidArray;
        //遍历，获取所有打钩控件
        int rows = ui->tab_file->rowCount();
        for(int i=0; i<rows; ++i){
            //获取文件id
            MyTableWidgetItem *item = (MyTableWidgetItem*)ui->tab_file->item(i, 0);
            int fileid;
            //查看是否被勾选
            if(item->checkState() == Qt::Checked){
                //添加文件id
                fileid = item->m_info.fileid;
                fileidArray.push_back(fileid);
            }
        }
        //发送信号
        QString path = ui->pb_filePath->text();
        Q_EMIT SIG_deleteFile(path, fileidArray);
    }else if(act->text() == "分享"){
        qDebug() << "分享";
        QVector<int> fileidArray;
        //遍历，获取所有打钩控件
        int rows = ui->tab_file->rowCount();
        for(int i=0; i<rows; ++i){
            //获取文件id
            MyTableWidgetItem *item = (MyTableWidgetItem*)ui->tab_file->item(i, 0);
            int fileid;
            //查看是否被勾选
            if(item->checkState() == Qt::Checked){
                //添加文件id
                fileid = item->m_info.fileid;
                fileidArray.push_back(fileid);
            }
        }
        //发送信号
        QString path = ui->pb_filePath->text();
        Q_EMIT SIG_shareFile(path, fileidArray);
    }else if(act->text() == "收藏"){
        qDebug() << "收藏";
    }else if(act->text() == "获取分享"){
        qDebug() << "获取分享";
        //弹窗 输出分享码
        QString txt = QInputDialog::getText(this, "获取分享", "输入分享码");
        int link = txt.toInt();
        if(txt.length() != 8 || link > 100000000 || link < 10000000 ){
            QMessageBox::about(this, "提示", "非法分享码");
            return;
        }
        QString path = ui->pb_filePath->text();
        Q_EMIT SIG_getShare(path, link);
    }
}

void MainDialog::slot_dealMenuUploadFile(QAction *act)
{
    if(act->text() == "暂停"){
        qDebug() << "Upload暂停";
        //遍历
        int rows = ui->table_upload->rowCount();
        qDebug() << "rows = " << rows;
        for(int i=0; i<rows; ++i){
            //查看是否选中
            MyTableWidgetItem* item = (MyTableWidgetItem*)ui->table_upload->item(i, 0);
            if(item->checkState() == Qt::Checked){
                //查看是否为暂停状态
                QPushButton* pButton = (QPushButton*)ui->table_upload->cellWidget(i, 3);
                if(pButton->text() == "暂停"){
                    pButton->setText("开始");
                    Q_EMIT SIG_setUploadPause(item->m_info.fileid, 1);
                }
            }
        }
    }else if(act->text() == "开始"){
        qDebug() << "Upload开始";
        //遍历
        int rows = ui->table_upload->rowCount();
        for(int i=0; i<rows; ++i){
            //查看是否选中
            MyTableWidgetItem* item = (MyTableWidgetItem*)ui->table_upload->item(i, 0);
            if(item->checkState() == Qt::Checked){
                //查看是否为暂停状态
                QPushButton* pButton = (QPushButton*)ui->table_upload->cellWidget(i, 3);
                if(pButton->text() == "开始"){
                    pButton->setText("暂停");
                    Q_EMIT SIG_setUploadPause(item->m_info.fileid, 0);
                }
            }
        }
    }
}

void MainDialog::slot_dealMenuDownloadFile(QAction *act)
{
    if(act->text() == "暂停"){
        qDebug() << "Download暂停";
        //遍历
        int rows = ui->table_download->rowCount();
        for(int i=0; i<rows; ++i){
            //查看是否选中
            MyTableWidgetItem* item = (MyTableWidgetItem*)ui->table_download->item(i, 0);
            if(item->checkState() == Qt::Checked){
                //查看是否为暂停状态
                QPushButton* pButton = (QPushButton*)ui->table_download->cellWidget(i, 3);
                if(pButton->text() == "暂停"){
                    pButton->setText("开始");
                    Q_EMIT SIG_setDownloadPause(item->m_info.fileid, 1);
                }
            }
        }
    }else if(act->text() == "开始"){
        qDebug() << "Download开始";
        //遍历
        int rows = ui->table_download->rowCount();
        for(int i=0; i<rows; ++i){
            //查看是否选中
            MyTableWidgetItem* item = (MyTableWidgetItem*)ui->table_download->item(i, 0);
            if(item->checkState() == Qt::Checked){
                //查看是否为暂停状态
                QPushButton* pButton = (QPushButton*)ui->table_download->cellWidget(i, 3);
                if(pButton->text() == "开始"){
                    pButton->setText("暂停");
                    Q_EMIT SIG_setDownloadPause(item->m_info.fileid, 0);
                }
            }
        }
    }
}
#include<QFileDialog>
void MainDialog::slot_dealMenuAddFile(QAction *act)
{
    //查看上传类别
    if(act->text() == "上传文件"){
        qDebug() << "上传文件";
        //弹窗 选择文件
        QString path = QFileDialog::getOpenFileName(this, "上传文件");
        if(path.isEmpty()){
            return;
        }
        //判断是否在上传列表
        QFileInfo info(path);
        int rows = ui->tab_file->currentRow();
        for(int i=0; i<rows; ++i){
            //获取文件id
            MyTableWidgetItem *item = (MyTableWidgetItem*)ui->table_upload->item(i, 0);
            //查看是否重名
            if(item->m_info.fileid == info.fileName()){
                //报错,返回
                QMessageBox::about(this, "提示", "文件正在上传");
                return;
            }
        }
        //发送信号 让核心类处理 发送上传请求
        Q_EMIT SIG_uploadFile(path);
    }else if(act->text() == "上传文件夹"){
        qDebug() << "上传文件夹";
        //弹窗 选择路径
        QString path = QFileDialog::getExistingDirectory(this, "选择文件夹", "./");
        QFileInfo info(path);
        if(path.isEmpty()) return;
        //过滤
        int rows = ui->tab_file->currentRow();
        for(int i=0; i<rows; ++i){
            //获取文件id
            MyTableWidgetItem *item = (MyTableWidgetItem*)ui->tab_file->item(i, 0);
            //查看是否重名
            if(item->m_info.fileid == info.fileName()){
                //报错,返回
                QMessageBox::about(this, "提示", "文件名重复");
                return;
            }
        }
        Q_EMIT SIG_uploadFolder(path);
    }
}

void MainDialog::on_tab_file_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->tab_file->item(row, 0);
    if(item->checkState() == Qt::Unchecked)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
}


void MainDialog::on_pb_addFile_clicked()
{
    //弹出菜单
    m_menuAddFile.exec(QCursor::pos());
}


void MainDialog::on_tab_file_cellDoubleClicked(int row, int column)
{
    //路径跳转
    MyTableWidgetItem* item =
            (MyTableWidgetItem*)ui->tab_file->item(row, 0);
    if(item->m_info.fileType != "file"){
        //获取当前路径 + 点击文件夹路径
        QString path = ui->pb_filePath->text() + ui->tab_file->item(row, 0)->text() + "/";
        ui->pb_filePath->setText(path);

        Q_EMIT SIG_changePath( path );
    }
}


void MainDialog::on_pb_preDir_clicked()
{
    //路径跳转
    QString path = ui->pb_filePath->text();
    if(path == "/") return;
    // /root/test/ -> /root/test -> /root/
    path = path.left(path.lastIndexOf("/"));//截取到最后一个"/"之前
    path = path.left(path.lastIndexOf("/") + 1);//截取到最后一个"/"
    ui->pb_filePath->setText(path);

    Q_EMIT SIG_changePath( path );
}


void MainDialog::on_table_upload_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->table_upload->item(row, 0);
    if(item->checkState() == Qt::Unchecked)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
}


void MainDialog::on_table_download_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->table_download->item(row, 0);
    if(item->checkState() == Qt::Unchecked)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
}

