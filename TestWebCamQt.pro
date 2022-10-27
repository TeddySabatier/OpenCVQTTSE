#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T15:06:48
#
#-------------------------------------------------

QT       += core gui opengl widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestWebCamQt
TEMPLATE = app


# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}

SOURCES += main.cpp\
        asteroid.cpp \
        displayw.cpp \
        objectsposition.cpp \
        spacebase.cpp \
        spaceship.cpp \
        spacestars.cpp \
        widget.cpp

HEADERS  += widget.h \
    asteroid.h \
    displayw.h \
    objectsposition.h \
    spacebase.h \
    spaceship.h \
    spacestars.h

FORMS    += widget.ui

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core455 \
    -lopencv_highgui455 \
    -lopencv_imgproc455 \
    -lopencv_imgcodecs455 \
    -lopencv_videoio455 \
    -lopencv_features2d455 \
    -lopencv_calib3d455 \
    -lopencv_objdetect455

RESOURCES += ressources/res.qrc
