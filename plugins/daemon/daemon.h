#pragma once

#include <QObject>
#include <QVersionNumber>

/**
 * @brief The Daemon class
 */
class Daemon : public QObject {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.pastillilabs.situations-daemon.daemon")

public:
    Daemon(QObject* parent = nullptr);

    Q_INVOKABLE QVersionNumber version() const;
};
