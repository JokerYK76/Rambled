#ifndef MYTABLEWIDGETITEM_H
#define MYTABLEWIDGETITEM_H

#include <QTableWidget>
#include "common.h"

class MyTableWidgetItem : public QTableWidgetItem
{
//    Q_OBJECT
public:
    explicit MyTableWidgetItem();

    void setInfo(FileInfo& info);
    FileInfo m_info;
};

#endif // MYTABLEWIDGETITEM_H
