#include "launch.h"

#include <contentaction.h>
#include <mlite5/MDesktopEntry>
#include <mlite5/mdesktopentry.h>

#include <QSharedPointer>

Launch::Launch(QObject* parent)
    : QObject(parent) {}

void Launch::trigger(const QString& id) {
    QSharedPointer<MDesktopEntry> desktopEntry(new MDesktopEntry(id));

    ContentAction::Action action = ContentAction::Action::launcherAction(desktopEntry, {});
    action.trigger();
}
