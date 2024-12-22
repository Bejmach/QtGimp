QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aspectratiolabel.cpp \
    colorcorrectiongraph.cpp \
    dialogempty.cpp \
    dialogfresnel.cpp \
    dialoggaussian.cpp \
    dialogslider.cpp \
    layerpanel.cpp \
    main.cpp \
    mainwindow.cpp \
    pointholder.cpp \
    qtlayers.cpp \
    src/Color.cpp \
    src/GraphLayer.cpp \
    src/Graphs.cpp \
    src/Image.cpp \
    src/Layer.cpp \
    src/LayerEditor.cpp \
    src/Pixel.cpp \
    src/StringOperations.cpp \
    src/Vector.cpp

HEADERS += \
    aspectratiolabel.h \
    colorcorrectiongraph.h \
    dialogempty.h \
    dialogfresnel.h \
    dialoggaussian.h \
    dialogslider.h \
    layerpanel.h \
    mainwindow.h \
    pointholder.h \
    qtlayers.h \
    src/Color.hpp \
    src/GraphLayer.hpp \
    src/Graphs.hpp \
    src/Image.hpp \
    src/Layer.hpp \
    src/LayerEditor.hpp \
    src/Pixel.hpp \
    src/StringOperations.hpp \
    src/Vector.hpp

FORMS += \
    aspectratiolabel.ui \
    colorcorrectiongraph.ui \
    dialogempty.ui \
    dialogfresnel.ui \
    dialoggaussian.ui \
    dialogslider.ui \
    layerpanel.ui \
    mainwindow.ui \
    pointholder.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
