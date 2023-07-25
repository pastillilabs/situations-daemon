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
    mStorage->loadRecurringIncidences();

    KCalendarCore::Incidence::List incidences(mCalendar->incidences(startDate, endDate));
    const mKCal::ExtendedCalendar::ExpandedIncidenceList incidenceList(mCalendar->expandRecurrences(&incidences, QDateTime(startDate), QDateTime(endDate)));

    QJsonArray events;
    for(const mKCal::ExtendedCalendar::ExpandedIncidence& expandedIncident : incidenceList) {
        const mKCal::ExtendedCalendar::ExpandedIncidenceValidity& incidenceValidity(expandedIncident.first);
        const KCalendarCore::Incidence::Ptr incidence(expandedIncident.second);

        if(incidence->type() == KCalendarCore::IncidenceBase::TypeEvent) {
            const QString calendarUid(mCalendar->notebook(incidence));
            const mKCal::Notebook::Ptr notebook(mStorage->notebook(calendarUid));

            if(!notebook || !notebook->isVisible() || !notebook->eventsAllowed()) {
                continue;
            }

            const QJsonObject event{
                {QStringLiteral("calendarId"), calendarUid},
                {QStringLiteral("begin"), QString::number(incidenceValidity.dtStart.toMSecsSinceEpoch())},
                {QStringLiteral("end"), QString::number(incidenceValidity.dtEnd.toMSecsSinceEpoch())},
                {QStringLiteral("title"), incidence->summary()},
                {QStringLiteral("description"), incidence->description()},
                {QStringLiteral("eventLocation"), incidence->location()},
                {QStringLiteral("hasAlarm"), incidence->hasEnabledAlarms()},
                {QStringLiteral("rrule"), incidence->recurs() ? QStringLiteral("RRULE") : QString()},
                {QStringLiteral("allDay"), incidence->allDay()},
                {QStringLiteral("availability"), static_cast<int>(incidence->status())}
            };
            events.append(event);
        }
    }

    return events;
}

void Calendar::storageModified([[maybe_unused]] mKCal::ExtendedStorage* storage, [[maybe_unused]] const QString& info) {
    emit updated();
}
