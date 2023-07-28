TEMPLATE = subdirs

SUBDIRS += \
    plugins \

DISTFILES += \
    rpm/situations-daemon.changes \
    rpm/situations-daemon.spec \
    rpm/situations-daemon.yaml \

OTHER_FILES += \
    harbour-situations2application.profile \
    situations-daemon.service \

situations-profile.files = harbour-situations2application.profile
situations-profile.path = /etc/sailjail/permissions
situations-service.files = situations-daemon.service
situations-service.path = /etc/systemd/system
INSTALLS += situations-profile situations-service
