TEMPLATE = subdirs

SUBDIRS += \
    plugins \

DISTFILES += \
    rpm/situations-daemon.changes \
    rpm/situations-daemon.spec \
    rpm/situations-daemon.yaml \

OTHER_FILES += \
    situations-daemon.service \

situations-service.files = situations-daemon.service
situations-service.path = /etc/systemd/system
INSTALLS += situations-service
