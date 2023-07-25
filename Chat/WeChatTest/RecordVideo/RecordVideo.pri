
QT       += core gui

INCLUDEPATH+=D:\opencv\include\opencv\
             D:\opencv\include\opencv2\
             D:\opencv\include
LIBS+=D:\opencv\lib\libopencv_calib3d2410.dll.a\
      D:\opencv\lib\libopencv_contrib2410.dll.a\
      D:\opencv\lib\libopencv_core2410.dll.a\
      D:\opencv\lib\libopencv_features2d2410.dll.a\
      D:\opencv\lib\libopencv_flann2410.dll.a\
      D:\opencv\lib\libopencv_gpu2410.dll.a\
      D:\opencv\lib\libopencv_highgui2410.dll.a\
      D:\opencv\lib\libopencv_imgproc2410.dll.a\
      D:\opencv\lib\libopencv_legacy2410.dll.a\
      D:\opencv\lib\libopencv_ml2410.dll.a\
      D:\opencv\lib\libopencv_objdetect2410.dll.a\
      D:\opencv\lib\libopencv_video2410.dll.a

HEADERS += \
    $$PWD/screen_read.h \
    $$PWD/video_read.h \
    $$PWD/common.h \
    $$PWD/myfacedetect.h

SOURCES += \
    $$PWD/screen_read.cpp \
    $$PWD/video_read.cpp \
    $$PWD/myfacedetect.cpp



