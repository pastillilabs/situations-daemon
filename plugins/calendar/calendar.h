#pragma once

#include <mkcal-qt5/extendedcalendar.h>
#include <mkcal-qt5/extendedstorage.h>
#include <mkcal-qt5/extendedstorageobserver.h>

#include <QJsonArray>
#include <QObject>
#include <QSharedPointer>

/**
 * @brief The Calendar class
 */
class Calendar : public QObject, public mKCal::ExtendedStorageObserver {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.pastillilabs.situations-daemon.calendar")

public:
    Calendar(QObject* parent = nullptr);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    Q_INVOKABLE QJsonArray calendars() const;
    Q_INVOKABLE QJsonArray events() const;

signals:
    void updated();

public: // From mKCal::ExtendedStorageObserver
    void storageModified(mKCal::ExtendedStorage* /*storage*/, const QString& /*info*/) override;

private:
    mKCal::ExtendedCalendar::Ptr mCalendar;
    mKCal::ExtendedStorage::Ptr mStorage;
};
