#include "contacts.h"

#include <QJsonObject>
#include <QtContacts/QContact>
#include <QtContacts/QContactDetail>
#include <QtContacts/QContactDisplayLabel>
#include <QtContacts/QContactManager>
#include <QtContacts/QContactName>
#include <QtContacts/QContactPhoneNumber>

namespace {

const QString CONTACT_MANAGER_NAME(QStringLiteral("org.nemomobile.contacts.sqlite"));

QJsonArray toJsonArray(const QList<QtContacts::QContactPhoneNumber>& numbers) {
    QJsonArray jsonNumbers;
    for(const auto& numberDetail : numbers) {
        jsonNumbers.append(numberDetail.number());
    }

    return jsonNumbers;
}

} // namespace

Contacts::Contacts(QObject* parent)
    : QObject(parent) {}

QJsonArray Contacts::contacts() const {
    QJsonArray jsonContacts;

    const QtContacts::QContactManager contactManager(CONTACT_MANAGER_NAME);
    const QList<QtContacts::QContact> contacts(contactManager.contacts());

    for(const auto& contact : contacts) {
        const QJsonObject contactItem{
            {QStringLiteral("id"), contact.id().toString()},
            {QStringLiteral("name"), contact.detail<QtContacts::QContactDisplayLabel>().label()},
            {QStringLiteral("numbers"), toJsonArray(contact.details<QtContacts::QContactPhoneNumber>())}
        };

        jsonContacts.append(contactItem);
    }

    return jsonContacts;
}
