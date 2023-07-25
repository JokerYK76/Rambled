QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(./netapi/netapi.pri)
include(./RecordAudio/RecordAudio.pri)

INCLUDEPATH += ./netapi
INCLUDEPATH += ./RecordAudio

SOURCES += \
    addroom.cpp \
    chatdlg.cpp \
    ckernel.cpp \
    createroom.cpp \
    frienditem.cpp \
    friendlist.cpp \
    gameroomdialog.cpp \
    logindialog.cpp \
    main.cpp \
    maindialog.cpp \
    roomitem.cpp \
    roomlist.cpp

HEADERS += \
    addroom.h \
    chatdlg.h \
    ckernel.h \
    createroom.h \
    frienditem.h \
    friendlist.h \
    gameroomdialog.h \
    logindialog.h \
    maindialog.h \
    roomitem.h \
    roomlist.h

FORMS += \
    addroom.ui \
    chatdlg.ui \
    createroom.ui \
    frienditem.ui \
    friendlist.ui \
    gameroomdialog.ui \
    logindialog.ui \
    maindialog.ui \
    roomitem.ui \
    roomlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
