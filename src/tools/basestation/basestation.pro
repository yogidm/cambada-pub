######################################################################
# Automatically generated by qmake (2.01a) Mon Nov 23 21:57:51 2009
######################################################################

TEMPLATE = app
TARGET = ../bin/basestation
DEPENDPATH += . \
              FieldWidget \
              FullInfoWindow \
              FullWindow \
              LogWidget \
              MainWindow \
              RefBoxWidget \
              RobotInfoWidget \
              RobotWidget \
              UpdateWidget
INCLUDEPATH += . \
               MainWindow \
               FieldWidget \
               UpdateWidget \
               RefBoxWidget \
               LogWidget \
               RobotWidget \
               FullWindow \
               FullInfoWindow \
               RobotInfoWidget \
	       /usr/local/include/libxml++-1.0

# Input
HEADERS += FieldWidget/FieldWidget.h \
           FullInfoWindow/FullInfoWindow.h \
           FullWindow/FullWindow.h \
		   LogWidget/LogWidget.h \
           MainWindow/MainWindow.h \
           RefBoxWidget/RefBoxDialog.h \
           RefBoxWidget/RefBoxWidget.h \
           RefBoxWidget/RefBoxXML.h \
           RobotInfoWidget/RobotInfoWidget.h \
           RobotWidget/RobotDialog.h \
           RobotWidget/RobotWidget.h \
           UpdateWidget/DB_Robot_info.h \
		   UpdateWidget/UpdateWidget.h \
    FieldWidget/FieldWidget3D.h
FORMS += FullInfoWindow/FullInfoWindow_WG.ui \
         FullWindow/FullWindow.ui \
         LogWidget/LogWidget.ui \
         MainWindow/MainWindow.ui \
         RefBoxWidget/RefBoxDialog.ui \
         RefBoxWidget/RefBoxWG.ui \
         RobotInfoWidget/RobotInfoWG.ui \
         RobotWidget/RobotDialog.ui \
         RobotWidget/robotwidget.ui
SOURCES += main.cpp \
           FieldWidget/FieldWidget.cpp \
           FullInfoWindow/FullInfoWindow.cpp \
           FullWindow/FullWindow.cpp \
           LogWidget/LogWidget.cpp \
           MainWindow/MainWindow.cpp \
           RefBoxWidget/RefBoxDialog.cpp \
           RefBoxWidget/RefBoxWidget.cpp \
           RefBoxWidget/RefBoxXML.cpp \
           RobotInfoWidget/RobotInfoWidget.cpp \
           RobotWidget/RobotDialog.cpp \
           RobotWidget/RobotWidget.cpp \
		   UpdateWidget/UpdateWidget.cpp \
    FieldWidget/FieldWidget3D.cpp
RESOURCES += basestation.qrc

QT+=opengl
QT+=network
RESOURCES     = basestation.qrc
DEPENDPATH += -I../include/ -I/usr/include/vtk-5.8/
CONFIG += link_pkgconfig
PKGCONFIG += libxml++-1.0
INCLUDEPATH += ../include/ /usr/include/vtk-5.8/
LIBS+= -L../lib/ -lcomm -ltCambada -lrtdb -lworldstate -lutils -lxml2 -lpthread -lz -lm -lglut -lxerces-c -lxml++-1.0 -lxml2 -lQVTK
CONFIG -= debug
