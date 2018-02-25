TEMPLATE = app
TARGET = vokocamera

#QT += core gui widgets 
QT += multimedia multimediawidgets
QT += testlib

# Input
HEADERS += vokocamera.h

SOURCES += main.cpp \
           vokocamera.cpp

FORMS += surface.ui


# Install paths
isEmpty(PREFIX) {
    PREFIX = /usr
}

image.path = $$PREFIX/share/pixmaps
image.files += applications/vokoscreen.png
desktop.path = $$PREFIX/share/applications
desktop.files += applications/vokoscreen.desktop
man.path = $$PREFIX/share
man.files += man
target.path = $$PREFIX/bin

INSTALLS += target image desktop man

# Clean target
QMAKE_CLEAN += $$TARGET */*~

CONFIG += link_pkgconfig

# webcam
include(webcam/webcam.pri)

# settings
include(settings/settings.pri)

