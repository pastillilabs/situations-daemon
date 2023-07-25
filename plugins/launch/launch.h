#pragma once

#include <QObject>

/**
 * @brief The Launch class
 */
class Launch : public QObject {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.pastillilabs.situations-daemon.launch")

public:
    Launch(QObject* parent = nullptr);

    Q_INVOKABLE void trigger(const QString& id);
};
