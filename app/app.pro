QT += core serialport network widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(../RTKLib.pri)

#target.path = /home/pi
TEMPLATE = app

INCLUDEPATH += ../src/

linux{
    RTKLIB =../src/libRTKLib.a
    LIBS += $${RTKLIB}
    LIBS += -L"/home/user/Downloads/SFML-2.5.0/lib"

    CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
    CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

    INCLUDEPATH += "/home/user/Downloads/SFML-2.5.0/include"
    DEPENDPATH += "/home/user/Downloads/SFML-2.5.0/include"
}

win32 {
    CONFIG(release, debug|release): RTKLIB = ../src/release/libRTKLib.a
    CONFIG(debug, debug|release): RTKLIB = ../src/debug/libRTKLib.a

    LIBS+= $${RTKLIB} -lWs2_32 -lwinmm

    INCLUDEPATH += G:\RTK\Qt\SFML-2.5.0\include
    DEPENDPATH += G:\RTK\Qt\SFML-2.5.0\include

    LIBS += -LG:\RTK\Qt\SFML-2.5.0\lib\

    CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -lsfml-main
    CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
}

#win32 {
#    CONFIG(debug) {
#        RTKLIB = ../src/debug/libRTKLib.a
#    } else {
#        RTKLIB =../src/release/libRTKLib.a
#    }
#
#    LIBS+= $${RTKLIB} -lWs2_32 -lwinmm
#}

PRE_TARGETDEPS = $${RTKLIB}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    serial.cpp \
    rtkmain.cpp \
    rtksettings.cpp \
    mainwindow.cpp \
    borderlayout.cpp \
    stackbuttons.cpp \
    sfml/Field.cpp \
    sfml/GPSPoint.cpp \
    sfml/Path.cpp \
    sfml/Tool.cpp \
    sfml/Traktor.cpp \
    sfml_navigation.cpp \
    sfml_widget.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    serial.h \
    rtkmain.h \
    rtksettings.h \
    mainwindow.h \
    borderlayout.h \
    stackbuttons.h \
    sfml/Field.h \
    sfml/GPSPoint.h \
    sfml/Path.h \
    sfml/targetver.h \
    sfml/Tool.h \
    sfml/Traktor.h \
    sfml_navigation.h \
    sfml_widget.h
