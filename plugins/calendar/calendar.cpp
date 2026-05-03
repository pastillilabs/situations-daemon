#include "calendar.h"

#include <QJsonObject>
#include <QTimeZone>

Calendar::Calendar(QObject* parent)
    : QObject(parent)
    , mCalendar(new mKCal::ExtendedCalendar(QTimeZone::systemTimeZone()))
    , mStorage(mKCal::ExtendedCalendar::defaultStorage(mCalendar)) {}

void Calendar::start() {
    mStorage->open();
    mStorage->registerObserver(this);
}

void Calendar::stop() {
    mStorage->unregisterObserver(this);
    mStorage->close();
    mCalendar->close();
}

QJsonArray Calendar::calendars() const {
    QJsonArray calendars;

    const mKCal::Notebook::List notebooks = mStorage->notebooks();
    for(const mKCal::Notebook::Ptr& notebook : notebooks) {
        const QJsonObject calendar{
            {QStringLiteral("name"), notebook->name()},
            {QStringLiteral("id"), notebook->uid()}
        };
        calendars.append(calendar);
    }

    return calendars;
}

QJsonArray Calendar::events() const {
    const QDate startDate(QDate::currentDate().addDays(-1));
    const QDate endDate(QDate::currentDate().addDays(1));

    mStorage->load(startDate, endDate);

    KCalendarCore::Incidence::List incidences(mCalendar->incidences(startDate, endDate));

    QJsonArray jsonEvents;
    for(KCalendarCore::Incidence::Ptr& incidence : incidences) {
        if(incidence->type() == KCalendarCore::Incidence::TypeEvent) {
            const auto event = qSharedPointerCast<KCalendarCore::Event>(incidence);

            const QString calendarUid(mCalendar->notebook(incidence));
            const mKCal::Notebook::Ptr notebook(mStorage->notebook(calendarUid));

            if(!notebook || !notebook->isVisible() || !notebook->eventsAllowed()) {
                continue;
            }

            const QJsonObject jsonEvent{
                {QStringLiteral("calendarId"), calendarUid},
                {QStringLiteral("begin"), QString::number(event->dtStart().toMSecsSinceEpoch())},
                {QStringLiteral("end"), QString::number(event->dtEnd().toMSecsSinceEpoch())},
                {QStringLiteral("title"), incidence->summary()},
                {QStringLiteral("description"), incidence->description()},
                {QStringLiteral("eventLocation"), incidence->location()},
                {QStringLiteral("hasAlarm"), incidence->hasEnabledAlarms()},
                {QStringLiteral("rrule"), incidence->recurs() ? QStringLiteral("RRULE") : QString()},
                {QStringLiteral("allDay"), incidence->allDay()},
                {QStringLiteral("availability"), static_cast<int>(incidence->status())}
            };
            jsonEvents.append(jsonEvent);
        }
    }

    return jsonEvents;
}

void Calendar::storageModified([[maybe_unused]] mKCal::ExtendedStorage* storage, [[maybe_unused]] const QString& info) {
    emit updated();
}
