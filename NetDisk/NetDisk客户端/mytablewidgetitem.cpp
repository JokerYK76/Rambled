#include "mytablewidgetitem.h"

MyTableWidgetItem::MyTableWidgetItem()
{

}

void MyTableWidgetItem::setInfo(FileInfo &info)
{
    m_info = info;

    this->setText( info.name );
    //资源路径引用 ":/images/file.png"
    if(info.fileType == "file")
        this->setIcon( QIcon(":/images/file.png") );
    else
        this->setIcon( QIcon(":/images/folder.png") );
    //选中框
    this->setCheckState( Qt::Unchecked );
}
