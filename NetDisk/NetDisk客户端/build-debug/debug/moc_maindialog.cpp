/****************************************************************************
** Meta object code from reading C++ file 'maindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainDialog_t {
    QByteArrayData data[60];
    char stringdata0[956];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainDialog_t qt_meta_stringdata_MainDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainDialog"
QT_MOC_LITERAL(1, 11, 9), // "SIG_close"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 16), // "SIG_downloadFile"
QT_MOC_LITERAL(4, 39, 6), // "fileid"
QT_MOC_LITERAL(5, 46, 14), // "SIG_uploadFile"
QT_MOC_LITERAL(6, 61, 4), // "path"
QT_MOC_LITERAL(7, 66, 16), // "SIG_uploadFolder"
QT_MOC_LITERAL(8, 83, 13), // "SIG_addFolder"
QT_MOC_LITERAL(9, 97, 4), // "name"
QT_MOC_LITERAL(10, 102, 14), // "SIG_changePath"
QT_MOC_LITERAL(11, 117, 14), // "SIG_deleteFile"
QT_MOC_LITERAL(12, 132, 12), // "QVector<int>"
QT_MOC_LITERAL(13, 145, 11), // "fileidArray"
QT_MOC_LITERAL(14, 157, 13), // "SIG_shareFile"
QT_MOC_LITERAL(15, 171, 12), // "SIG_getShare"
QT_MOC_LITERAL(16, 184, 4), // "link"
QT_MOC_LITERAL(17, 189, 18), // "SIG_setUploadPause"
QT_MOC_LITERAL(18, 208, 6), // "fileId"
QT_MOC_LITERAL(19, 215, 9), // "pauseFlag"
QT_MOC_LITERAL(20, 225, 20), // "SIG_setDownloadPause"
QT_MOC_LITERAL(21, 246, 10), // "closeEvent"
QT_MOC_LITERAL(22, 257, 12), // "QCloseEvent*"
QT_MOC_LITERAL(23, 270, 5), // "event"
QT_MOC_LITERAL(24, 276, 23), // "on_pb_fillePage_clicked"
QT_MOC_LITERAL(25, 300, 26), // "on_pb_transmitPage_clicked"
QT_MOC_LITERAL(26, 327, 23), // "on_pb_sharePage_clicked"
QT_MOC_LITERAL(27, 351, 23), // "on_tab_file_cellClicked"
QT_MOC_LITERAL(28, 375, 3), // "row"
QT_MOC_LITERAL(29, 379, 6), // "column"
QT_MOC_LITERAL(30, 386, 13), // "slot_menuShow"
QT_MOC_LITERAL(31, 400, 5), // "point"
QT_MOC_LITERAL(32, 406, 19), // "slot_menuUploadShow"
QT_MOC_LITERAL(33, 426, 21), // "slot_menuDownloadShow"
QT_MOC_LITERAL(34, 448, 13), // "slot_dealMenu"
QT_MOC_LITERAL(35, 462, 8), // "QAction*"
QT_MOC_LITERAL(36, 471, 3), // "act"
QT_MOC_LITERAL(37, 475, 23), // "slot_dealMenuUploadFile"
QT_MOC_LITERAL(38, 499, 25), // "slot_dealMenuDownloadFile"
QT_MOC_LITERAL(39, 525, 20), // "slot_dealMenuAddFile"
QT_MOC_LITERAL(40, 546, 23), // "slot_insertDownloadFile"
QT_MOC_LITERAL(41, 570, 9), // "FileInfo&"
QT_MOC_LITERAL(42, 580, 4), // "info"
QT_MOC_LITERAL(43, 585, 19), // "slot_insertComplete"
QT_MOC_LITERAL(44, 605, 23), // "slot_updateFileProgress"
QT_MOC_LITERAL(45, 629, 3), // "pos"
QT_MOC_LITERAL(46, 633, 21), // "slot_insertUploadFile"
QT_MOC_LITERAL(47, 655, 25), // "slot_insertUploadComplete"
QT_MOC_LITERAL(48, 681, 29), // "slot_updateUploadFileProgress"
QT_MOC_LITERAL(49, 711, 16), // "slot_insertShare"
QT_MOC_LITERAL(50, 728, 4), // "size"
QT_MOC_LITERAL(51, 733, 4), // "time"
QT_MOC_LITERAL(52, 738, 22), // "slot_folderButtonClick"
QT_MOC_LITERAL(53, 761, 32), // "slot_getDownloadFileInfoByFileID"
QT_MOC_LITERAL(54, 794, 30), // "slot_getUploadFileInfoByFileID"
QT_MOC_LITERAL(55, 825, 21), // "on_pb_addFile_clicked"
QT_MOC_LITERAL(56, 847, 29), // "on_tab_file_cellDoubleClicked"
QT_MOC_LITERAL(57, 877, 20), // "on_pb_preDir_clicked"
QT_MOC_LITERAL(58, 898, 27), // "on_table_upload_cellClicked"
QT_MOC_LITERAL(59, 926, 29) // "on_table_download_cellClicked"

    },
    "MainDialog\0SIG_close\0\0SIG_downloadFile\0"
    "fileid\0SIG_uploadFile\0path\0SIG_uploadFolder\0"
    "SIG_addFolder\0name\0SIG_changePath\0"
    "SIG_deleteFile\0QVector<int>\0fileidArray\0"
    "SIG_shareFile\0SIG_getShare\0link\0"
    "SIG_setUploadPause\0fileId\0pauseFlag\0"
    "SIG_setDownloadPause\0closeEvent\0"
    "QCloseEvent*\0event\0on_pb_fillePage_clicked\0"
    "on_pb_transmitPage_clicked\0"
    "on_pb_sharePage_clicked\0on_tab_file_cellClicked\0"
    "row\0column\0slot_menuShow\0point\0"
    "slot_menuUploadShow\0slot_menuDownloadShow\0"
    "slot_dealMenu\0QAction*\0act\0"
    "slot_dealMenuUploadFile\0"
    "slot_dealMenuDownloadFile\0"
    "slot_dealMenuAddFile\0slot_insertDownloadFile\0"
    "FileInfo&\0info\0slot_insertComplete\0"
    "slot_updateFileProgress\0pos\0"
    "slot_insertUploadFile\0slot_insertUploadComplete\0"
    "slot_updateUploadFileProgress\0"
    "slot_insertShare\0size\0time\0"
    "slot_folderButtonClick\0"
    "slot_getDownloadFileInfoByFileID\0"
    "slot_getUploadFileInfoByFileID\0"
    "on_pb_addFile_clicked\0"
    "on_tab_file_cellDoubleClicked\0"
    "on_pb_preDir_clicked\0on_table_upload_cellClicked\0"
    "on_table_download_cellClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  204,    2, 0x06 /* Public */,
       3,    1,  205,    2, 0x06 /* Public */,
       5,    1,  208,    2, 0x06 /* Public */,
       7,    1,  211,    2, 0x06 /* Public */,
       8,    1,  214,    2, 0x06 /* Public */,
      10,    1,  217,    2, 0x06 /* Public */,
      11,    2,  220,    2, 0x06 /* Public */,
      14,    2,  225,    2, 0x06 /* Public */,
      15,    2,  230,    2, 0x06 /* Public */,
      17,    2,  235,    2, 0x06 /* Public */,
      20,    2,  240,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    1,  245,    2, 0x0a /* Public */,
      24,    0,  248,    2, 0x0a /* Public */,
      25,    0,  249,    2, 0x0a /* Public */,
      26,    0,  250,    2, 0x0a /* Public */,
      27,    2,  251,    2, 0x0a /* Public */,
      30,    1,  256,    2, 0x0a /* Public */,
      32,    1,  259,    2, 0x0a /* Public */,
      33,    1,  262,    2, 0x0a /* Public */,
      34,    1,  265,    2, 0x0a /* Public */,
      37,    1,  268,    2, 0x0a /* Public */,
      38,    1,  271,    2, 0x0a /* Public */,
      39,    1,  274,    2, 0x0a /* Public */,
      40,    1,  277,    2, 0x0a /* Public */,
      43,    1,  280,    2, 0x0a /* Public */,
      44,    2,  283,    2, 0x0a /* Public */,
      46,    1,  288,    2, 0x0a /* Public */,
      47,    1,  291,    2, 0x0a /* Public */,
      48,    2,  294,    2, 0x0a /* Public */,
      49,    4,  299,    2, 0x0a /* Public */,
      52,    0,  308,    2, 0x0a /* Public */,
      53,    1,  309,    2, 0x0a /* Public */,
      54,    1,  312,    2, 0x0a /* Public */,
      55,    0,  315,    2, 0x08 /* Private */,
      56,    2,  316,    2, 0x08 /* Private */,
      57,    0,  321,    2, 0x08 /* Private */,
      58,    2,  322,    2, 0x08 /* Private */,
      59,    2,  327,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12,    6,   13,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12,    6,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    6,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::QPoint,   31,
    QMetaType::Void, QMetaType::QPoint,   31,
    QMetaType::Void, QMetaType::QPoint,   31,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,   45,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    9,   50,   51,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,

       0        // eod
};

void MainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_close(); break;
        case 1: _t->SIG_downloadFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SIG_uploadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->SIG_uploadFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SIG_addFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->SIG_changePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->SIG_deleteFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 7: _t->SIG_shareFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 8: _t->SIG_getShare((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->SIG_setUploadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->SIG_setDownloadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 12: _t->on_pb_fillePage_clicked(); break;
        case 13: _t->on_pb_transmitPage_clicked(); break;
        case 14: _t->on_pb_sharePage_clicked(); break;
        case 15: _t->on_tab_file_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->slot_menuShow((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 17: _t->slot_menuUploadShow((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 18: _t->slot_menuDownloadShow((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 19: _t->slot_dealMenu((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 20: _t->slot_dealMenuUploadFile((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 21: _t->slot_dealMenuDownloadFile((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 22: _t->slot_dealMenuAddFile((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 23: _t->slot_insertDownloadFile((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 24: _t->slot_insertComplete((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 25: _t->slot_updateFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 26: _t->slot_insertUploadFile((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 27: _t->slot_insertUploadComplete((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 28: _t->slot_updateUploadFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->slot_insertShare((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 30: _t->slot_folderButtonClick(); break;
        case 31: _t->slot_getDownloadFileInfoByFileID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->slot_getUploadFileInfoByFileID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_pb_addFile_clicked(); break;
        case 34: _t->on_tab_file_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 35: _t->on_pb_preDir_clicked(); break;
        case 36: _t->on_table_upload_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 37: _t->on_table_download_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_close)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_downloadFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_uploadFile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_uploadFolder)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_addFolder)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_changePath)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString , QVector<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_deleteFile)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString , QVector<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_shareFile)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_getShare)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_setUploadPause)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainDialog::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainDialog::SIG_setDownloadPause)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_MainDialog.data,
    qt_meta_data_MainDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void MainDialog::SIG_close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainDialog::SIG_downloadFile(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainDialog::SIG_uploadFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainDialog::SIG_uploadFolder(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainDialog::SIG_addFolder(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainDialog::SIG_changePath(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainDialog::SIG_deleteFile(QString _t1, QVector<int> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainDialog::SIG_shareFile(QString _t1, QVector<int> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainDialog::SIG_getShare(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainDialog::SIG_setUploadPause(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainDialog::SIG_setDownloadPause(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
