QT += core gui widgets network
TARGET = MyApp
TEMPLATE = app


RESOURCES += myresources.qrc \
    resourcefield.qrc
SOURCES += \
    JalapenoMoveThread.cpp \
    ShootThread.cpp \
    SunBrainThread.cpp \
    energymanager.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    login.cpp \
    movethread.cpp \
    signup.cpp \
    forgetpassword.cpp \
    resetpassword.cpp \
    progressbarwindow.cpp


HEADERS += \
    JalapenoMoveThread.h \
    ShootThread.h \
    SunBrainThread.h \
    energymanager.h \
    form.h \
    mainwindow.h \
    login.h \
    movethread.h \
    signup.h \
    forgetpassword.h \
    resetpassword.h \
    progressbarwindow.h


FORMS += \
    form.ui \
    mainwindow.ui \
    forgetpassword.ui \
    login.ui \
    resetpassword.ui \
    signup.ui \
    forgetpassword.ui

RESOURCES += \
    myresources.qrc

