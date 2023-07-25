TEMPLATE = lib

QT = core
CONFIG += plugin
CONFIG += link_pkgconfig

PKGCONFIG += contentaction5 mlite5

QMAKE_RPATHDIR += /usr/share/situations-daemon/lib

HEADERS += $$files($$PWD/*.h)
SOURCES += $$files($$PWD/*.cpp)

target.path = /usr/share/situations-daemon/lib
INSTALLS += target
