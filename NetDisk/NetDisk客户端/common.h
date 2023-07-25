#ifndef COMMON_H
#define COMMON_H

#include<QString>
struct FileInfo{
    FileInfo(): fileid(0), size(0), pFile(nullptr), pos(0), isPause(0){}

    int fileid;
    QString name;
    QString time;
    int size;
    QString dir;
    QString md5;
    QString fileType;//file dir
    QString absolutePath;//绝对路径

    int pos;//文件传输位置

    int isPause;//暂停 0 1

    //文件指针
    FILE* pFile;

    static QString getSize(int size){
        QString res;
        int tmp = size;
        int count = 0;
        while(tmp != 0){
            tmp /= 1024;
            if(tmp != 0)
                ++count;
        }
        switch(count){
        case 0:
            res = QString("0.%1KB").arg( (int)(size/1024.0*1000), 3, 10, QChar('0'));
            break;
        case 1:
            res = QString("%1.%2KB").arg( size/1024 ).arg((int)(size%1024/1024.0*1000), 3, 10, QChar('0'));
            break;
        case 2:
        default:
            res = QString("%1.%2MB").arg( size/1024/1024 ).arg((int)(size/1024%1024/1024.0*1000), 3, 10, QChar('0'));
            break;
        }
        return res;
    }
};

#endif // COMMON_H
