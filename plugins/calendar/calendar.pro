TEMPLATE = lib

QT = core
CONFIG += plugin
CONFIG += link_pkgconfig

PKGCONFIG += KF5CalendarCore
PKGCONFIG += libical
PKGCONFIG += libmkcal-qt5

QMAKE_RPATHDIR += /usr/share/situations-daemon/lib

INCLUDEPATH += /usr/include/kcalcoren-qt5
INCLUDEPATH += /usr/include/mkcal-qt5

HEADERS += $$files($$PWD/*.h)
SOURCES += $$files($$PWD/*.cpp)

target.path = /usr/share/situations-daemon/lib
INSTALLS += target
