SOURCES += \
    main.cpp \
    server.cpp \
    serveropc.cpp \
    redisopc.cpp \
    myerropc.cpp \
    util.cpp \
    mysql.cpp

HEADERS += \
    server.h \
    def.h \
    serveropc.h \
    redisopc.h \
    myerropc.h \
    util.h \
    mysql.h

LIBS+=-L /usr/local/lib  -ltufao1 -lhiredis

QT+=network sql

CONFIG += C++11 console



