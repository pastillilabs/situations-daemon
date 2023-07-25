#include "daemon.h"

Daemon::Daemon(QObject* parent)
    : QObject(parent) {}

QVersionNumber Daemon::version() const {
    // Kepp in sync with version info in
    // - situations-daemon.conf
    // - situations-daemon.spec
    // - platformmanager.cpp
    return QVersionNumber(1, 0, 0);
}
