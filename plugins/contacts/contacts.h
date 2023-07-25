#pragma once

#include <QJsonArray>
#include <QObject>

/**
 * @brief The Contacts class
 */
class Contacts : public QObject {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.pastillilabs.situations-daemon.contacts")

public:
    Contacts(QObject* parent = nullptr);

    Q_INVOKABLE QJsonArray contacts() const;
};
