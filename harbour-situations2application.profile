# -*- mode: sh -*-

# Firejail profile for /usr/bin/harbour-situations2application

# x-sailjail-translation-catalog = harbour-situations2application
# x-sailjail-translation-key-description = permission-la-data
# x-sailjail-description = Situations Server Socket permission
# x-sailjail-translation-key-long-description = permission-la-data_description
# x-sailjail-long-description = Communicate with the daemon

### PERMISSIONS
# x-sailjail-permission = Documents
# x-sailjail-permission = Downloads
# x-sailjail-permission = Internet
# x-sailjail-permission = Location

include /etc/sailjail/permissions/Documents.permission
include /etc/sailjail/permissions/Downloads.permission
include /etc/sailjail/permissions/Internet.permission
include /etc/sailjail/permissions/Location.permission

whitelist /tmp/situationsserver
