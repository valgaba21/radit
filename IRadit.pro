#-------------------------------------------------
#
# Project created by QtCreator 2014-01-15T12:41:13
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IRadit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player/Player.cpp \
    micelanea/Dock/Dock.cpp \
    toolbar/ToolBar.cpp \
    tab/Tab.cpp \
    button/Button.cpp \
    setting/Setting.cpp \
    about/About.cpp \
    iostream/Iostream.cpp \
    engine/StreamFile.cpp \
    engine/StreamMath.cpp \
    menu/MenuButton.cpp \
    menu/MenuTab.cpp \
    engine/Fader.cpp \
    engine/StreamPlay.cpp \
    engine/StreamRender.cpp \
    render/Render.cpp \
    explore/Explore.cpp \
    explore/TableView/TableView.cpp \
    menu/MenuExplore.cpp

HEADERS  += mainwindow.h \
    player/Player.h \
    micelanea/Dock/Dock.h \
    toolbar/ToolBar.h \
    tab/Tab.h \
    button/Button.h \
    setting/Setting.h \
    about/About.h \
    iostream/Iostream.h \
    engine/StreamFile.h \
    engine/StreamMath.h \
    menu/MenuButton.h \
    menu/MenuTab.h \
    engine/Fader.h \
    engine/StreamPlay.h \
    engine/StreamRender.h \
    render/Render.h \
    explore/Explore.h \
    explore/TableView/TableView.h \
    menu/MenuExplore.h

FORMS    += mainwindow.ui \
    player/FrmPlayer.ui \
    toolbar/FrmToolBar.ui \
    tab/FrmTab.ui \
    setting/FrmSetting.ui \
    about/FrmAbout.ui \
    explore/FrmExplore.ui





# -------------------------------------------------
# mis lib
# -------------------------------------------------


win32 {

LIBS += ..\lib\bass\bass.lib \
        ..\lib\vumeter\libqvumeterplug.a \
        ..\lib\taglib\lib\libtag.dll.a

INCLUDEPATH = ..\lib\bass \
              ..\lib\vumeter \
              ..\lib\taglib\include\taglib



OBJECTS_DIR =../out
MOC_DIR = ../out
#UI_DIR = ../out
DESTDIR = ../IRadit-1.0-win32


}
#-----------------------------------------------------------

unix {

LIBS += /usr/lib/libbass.so \
       /usr/lib/libqvumeterplug.so \
      /usr/lib/libtag.so.1



INCLUDEPATH = ../lib/bass \
              ../lib/taglib/include/taglib \
              ../lib/vumeter



OBJECTS_DIR =../out
MOC_DIR = ../out
UI_DIR = ../out
DESTDIR = ../LinuxDesktop



}



#-------------------------------------------------------------
RESOURCES += \
    radit.qrc


RC_FILE = radit.rc








