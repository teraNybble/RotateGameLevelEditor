QT       += core gui opengl
LIBS += -lopengl32 -glu32 -png

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colour.cpp \
    enemy.cpp \
    leveleditorwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    movingplatform.cpp \
    rect.cpp \
    rectorganiser.cpp \
    sprite.cpp

HEADERS += \
    colour.h \
    enemy.h \
    leveleditorwindow.h \
    mainwindow.h \
    movingplatform.h \
    rect.h \
    rectorganiser.h \
    sprite.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    gamename69levelEditor_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
