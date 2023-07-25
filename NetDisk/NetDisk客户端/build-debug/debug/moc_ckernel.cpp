/****************************************************************************
** Meta object code from reading C++ file 'ckernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ckernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ckernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CKernel_t {
    QByteArrayData data[63];
    char stringdata0[965];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CKernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CKernel_t qt_meta_stringdata_CKernel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CKernel"
QT_MOC_LITERAL(1, 8, 22), // "SIG_updateFileProgress"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "fileid"
QT_MOC_LITERAL(4, 39, 3), // "pos"
QT_MOC_LITERAL(5, 43, 28), // "SIG_updateUploadFileProgress"
QT_MOC_LITERAL(6, 72, 20), // "slot_destroyInstance"
QT_MOC_LITERAL(7, 93, 20), // "slot_clientReadyData"
QT_MOC_LITERAL(8, 114, 7), // "lSendIP"
QT_MOC_LITERAL(9, 122, 5), // "char*"
QT_MOC_LITERAL(10, 128, 3), // "buf"
QT_MOC_LITERAL(11, 132, 4), // "nlen"
QT_MOC_LITERAL(12, 137, 20), // "slot_serverReadyData"
QT_MOC_LITERAL(13, 158, 17), // "slot_dealRegistRs"
QT_MOC_LITERAL(14, 176, 16), // "slot_dealLoginRs"
QT_MOC_LITERAL(15, 193, 17), // "slot_dealFileInfo"
QT_MOC_LITERAL(16, 211, 19), // "slot_dealFileHeadRq"
QT_MOC_LITERAL(17, 231, 25), // "slot_dealFolderDownLoadRq"
QT_MOC_LITERAL(18, 257, 22), // "slot_dealFileContentRq"
QT_MOC_LITERAL(19, 280, 25), // "slot_dealUploadFileHeadRs"
QT_MOC_LITERAL(20, 306, 22), // "slot_dealFileContentRs"
QT_MOC_LITERAL(21, 329, 20), // "slot_dealAddFolderRs"
QT_MOC_LITERAL(22, 350, 26), // "slot_dealQuickUploadFileRs"
QT_MOC_LITERAL(23, 377, 21), // "slot_dealDeleteFileRs"
QT_MOC_LITERAL(24, 399, 20), // "slot_dealShareFileRs"
QT_MOC_LITERAL(25, 420, 18), // "slot_dealMyShareRs"
QT_MOC_LITERAL(26, 439, 19), // "slot_dealGetShareRs"
QT_MOC_LITERAL(27, 459, 23), // "slot_dealGetUploadPosRs"
QT_MOC_LITERAL(28, 483, 15), // "slot_uploadFile"
QT_MOC_LITERAL(29, 499, 4), // "path"
QT_MOC_LITERAL(30, 504, 3), // "dir"
QT_MOC_LITERAL(31, 508, 17), // "slot_uploadFolder"
QT_MOC_LITERAL(32, 526, 19), // "slot_registerCommit"
QT_MOC_LITERAL(33, 546, 3), // "tel"
QT_MOC_LITERAL(34, 550, 3), // "pwd"
QT_MOC_LITERAL(35, 554, 4), // "name"
QT_MOC_LITERAL(36, 559, 16), // "slot_loginCommit"
QT_MOC_LITERAL(37, 576, 17), // "slot_downloadFile"
QT_MOC_LITERAL(38, 594, 14), // "slot_addFolder"
QT_MOC_LITERAL(39, 609, 15), // "slot_changePath"
QT_MOC_LITERAL(40, 625, 15), // "slot_deleteFile"
QT_MOC_LITERAL(41, 641, 12), // "QVector<int>"
QT_MOC_LITERAL(42, 654, 11), // "fileidArray"
QT_MOC_LITERAL(43, 666, 14), // "slot_shareFile"
QT_MOC_LITERAL(44, 681, 19), // "slot_refreshMyShare"
QT_MOC_LITERAL(45, 701, 13), // "slot_getShare"
QT_MOC_LITERAL(46, 715, 4), // "link"
QT_MOC_LITERAL(47, 720, 19), // "slot_setUploadPause"
QT_MOC_LITERAL(48, 740, 6), // "fileId"
QT_MOC_LITERAL(49, 747, 9), // "pauseFlag"
QT_MOC_LITERAL(50, 757, 21), // "slot_setDownloadPause"
QT_MOC_LITERAL(51, 779, 12), // "initDatabase"
QT_MOC_LITERAL(52, 792, 2), // "id"
QT_MOC_LITERAL(53, 795, 20), // "slot_writeUploadTask"
QT_MOC_LITERAL(54, 816, 9), // "FileInfo&"
QT_MOC_LITERAL(55, 826, 4), // "info"
QT_MOC_LITERAL(56, 831, 22), // "slot_writeDownloadTask"
QT_MOC_LITERAL(57, 854, 21), // "slot_deleteUploadTask"
QT_MOC_LITERAL(58, 876, 23), // "slot_deleteDownloadTask"
QT_MOC_LITERAL(59, 900, 18), // "slot_getUploadTask"
QT_MOC_LITERAL(60, 919, 16), // "QList<FileInfo>&"
QT_MOC_LITERAL(61, 936, 7), // "lstInfo"
QT_MOC_LITERAL(62, 944, 20) // "slot_getDownloadTask"

    },
    "CKernel\0SIG_updateFileProgress\0\0fileid\0"
    "pos\0SIG_updateUploadFileProgress\0"
    "slot_destroyInstance\0slot_clientReadyData\0"
    "lSendIP\0char*\0buf\0nlen\0slot_serverReadyData\0"
    "slot_dealRegistRs\0slot_dealLoginRs\0"
    "slot_dealFileInfo\0slot_dealFileHeadRq\0"
    "slot_dealFolderDownLoadRq\0"
    "slot_dealFileContentRq\0slot_dealUploadFileHeadRs\0"
    "slot_dealFileContentRs\0slot_dealAddFolderRs\0"
    "slot_dealQuickUploadFileRs\0"
    "slot_dealDeleteFileRs\0slot_dealShareFileRs\0"
    "slot_dealMyShareRs\0slot_dealGetShareRs\0"
    "slot_dealGetUploadPosRs\0slot_uploadFile\0"
    "path\0dir\0slot_uploadFolder\0"
    "slot_registerCommit\0tel\0pwd\0name\0"
    "slot_loginCommit\0slot_downloadFile\0"
    "slot_addFolder\0slot_changePath\0"
    "slot_deleteFile\0QVector<int>\0fileidArray\0"
    "slot_shareFile\0slot_refreshMyShare\0"
    "slot_getShare\0link\0slot_setUploadPause\0"
    "fileId\0pauseFlag\0slot_setDownloadPause\0"
    "initDatabase\0id\0slot_writeUploadTask\0"
    "FileInfo&\0info\0slot_writeDownloadTask\0"
    "slot_deleteUploadTask\0slot_deleteDownloadTask\0"
    "slot_getUploadTask\0QList<FileInfo>&\0"
    "lstInfo\0slot_getDownloadTask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CKernel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  229,    2, 0x06 /* Public */,
       5,    2,  234,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  239,    2, 0x08 /* Private */,
       7,    3,  240,    2, 0x08 /* Private */,
      12,    3,  247,    2, 0x08 /* Private */,
      13,    3,  254,    2, 0x08 /* Private */,
      14,    3,  261,    2, 0x08 /* Private */,
      15,    3,  268,    2, 0x08 /* Private */,
      16,    3,  275,    2, 0x08 /* Private */,
      17,    3,  282,    2, 0x08 /* Private */,
      18,    3,  289,    2, 0x08 /* Private */,
      19,    3,  296,    2, 0x08 /* Private */,
      20,    3,  303,    2, 0x08 /* Private */,
      21,    3,  310,    2, 0x08 /* Private */,
      22,    3,  317,    2, 0x08 /* Private */,
      23,    3,  324,    2, 0x08 /* Private */,
      24,    3,  331,    2, 0x08 /* Private */,
      25,    3,  338,    2, 0x08 /* Private */,
      26,    3,  345,    2, 0x08 /* Private */,
      27,    3,  352,    2, 0x08 /* Private */,
      28,    1,  359,    2, 0x08 /* Private */,
      28,    2,  362,    2, 0x08 /* Private */,
      31,    1,  367,    2, 0x08 /* Private */,
      31,    2,  370,    2, 0x08 /* Private */,
      32,    3,  375,    2, 0x08 /* Private */,
      36,    2,  382,    2, 0x08 /* Private */,
      37,    1,  387,    2, 0x08 /* Private */,
      38,    1,  390,    2, 0x08 /* Private */,
      38,    2,  393,    2, 0x08 /* Private */,
      39,    1,  398,    2, 0x08 /* Private */,
      40,    2,  401,    2, 0x08 /* Private */,
      43,    2,  406,    2, 0x08 /* Private */,
      44,    0,  411,    2, 0x08 /* Private */,
      45,    2,  412,    2, 0x08 /* Private */,
      47,    2,  417,    2, 0x08 /* Private */,
      50,    2,  422,    2, 0x08 /* Private */,
      51,    1,  427,    2, 0x08 /* Private */,
      53,    1,  430,    2, 0x08 /* Private */,
      56,    1,  433,    2, 0x08 /* Private */,
      57,    1,  436,    2, 0x08 /* Private */,
      58,    1,  439,    2, 0x08 /* Private */,
      59,    1,  442,    2, 0x08 /* Private */,
      62,    1,  445,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, QMetaType::Int,    8,   10,   11,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   30,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   30,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   33,   34,   35,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,   34,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   30,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 41,   29,   42,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 41,   29,   42,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   29,   46,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   48,   49,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   48,   49,
    QMetaType::Void, QMetaType::Int,   52,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,

       0        // eod
};

void CKernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CKernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_updateFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SIG_updateUploadFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_destroyInstance(); break;
        case 3: _t->slot_clientReadyData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->slot_serverReadyData((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->slot_dealRegistRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->slot_dealLoginRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->slot_dealFileInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->slot_dealFileHeadRq((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->slot_dealFolderDownLoadRq((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->slot_dealFileContentRq((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->slot_dealUploadFileHeadRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->slot_dealFileContentRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->slot_dealAddFolderRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 14: _t->slot_dealQuickUploadFileRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 15: _t->slot_dealDeleteFileRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 16: _t->slot_dealShareFileRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->slot_dealMyShareRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 18: _t->slot_dealGetShareRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 19: _t->slot_dealGetUploadPosRs((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 20: _t->slot_uploadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->slot_uploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 22: _t->slot_uploadFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->slot_uploadFolder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 24: _t->slot_registerCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 25: _t->slot_loginCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 26: _t->slot_downloadFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->slot_addFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->slot_addFolder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->slot_changePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->slot_deleteFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 31: _t->slot_shareFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 32: _t->slot_refreshMyShare(); break;
        case 33: _t->slot_getShare((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 34: _t->slot_setUploadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 35: _t->slot_setDownloadPause((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 36: _t->initDatabase((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->slot_writeUploadTask((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 38: _t->slot_writeDownloadTask((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 39: _t->slot_deleteUploadTask((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 40: _t->slot_deleteDownloadTask((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 41: _t->slot_getUploadTask((*reinterpret_cast< QList<FileInfo>(*)>(_a[1]))); break;
        case 42: _t->slot_getDownloadTask((*reinterpret_cast< QList<FileInfo>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CKernel::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CKernel::SIG_updateFileProgress)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CKernel::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CKernel::SIG_updateUploadFileProgress)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CKernel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CKernel.data,
    qt_meta_data_CKernel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CKernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CKernel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CKernel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CKernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void CKernel::SIG_updateFileProgress(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CKernel::SIG_updateUploadFileProgress(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
