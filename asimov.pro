QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asimov_library.cpp \
    help_dialog.cpp \
    main.cpp \
    main_asimov.cpp

HEADERS += \
    asimov_library.h \
    help_dialog.h \
    main_asimov.h

FORMS += \
    help_dialog.ui \
    main_asimov.ui

RESOURCES += \
    img/images.qrc \
    img/style.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    palabras_clave.txt \
    prueba_asimov.txt \
    script.py
