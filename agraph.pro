HEADERS       = \
    agraph.h \ 
    readCom.h \
    graphView.h \
    graphScene.h \
    graphKey.h \
    graphValue.h

SOURCES       = \
    agraph.cpp \
    main.cpp \
    readCom.cpp \
    graphView.cpp \
    graphScene.cpp \
    graphKey.cpp \
    graphValue.cpp


CODECFORTR    = ISO-8859-1

# install
target.path = .
#sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS tools.pro README
#sources.path = $$[QT_INSTALL_EXAMPLES]/tools
INSTALLS += target
QT +=  core gui widgets
#CONFIG += qt release
CONFIG += qt ordered static debug
#LFLAGS = -static-libgcc
#QMAKE_LFLAGS += -static-libgcc









