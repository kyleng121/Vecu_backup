QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    gRPC_shared_lib/lib_grpc_jetson/grpc_client_interface.hpp \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/gRPC_shared_lib/lib_grpc_jetson/release/ -lgrpc_client
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/gRPC_shared_lib/lib_grpc_jetson/debug/ -lgrpc_client
else:unix: LIBS += -L$$PWD/gRPC_shared_lib/lib_grpc_jetson/ -lgrpc_client

INCLUDEPATH += $$PWD/gRPC_shared_lib/lib_grpc_jetson
DEPENDPATH += $$PWD/gRPC_shared_lib/lib_grpc_jetson

DISTFILES += \
    gRPC_shared_lib/lib_grpc_jetson/libgrpc_client.so
