#!/bin/bash
echo "Installing..."

if [ ! -d /opt/uds/bin ] ; then
    mkdir -p /opt/uds/bin
fi

if [ ! -d /opt/uds/icons/apps ] ; then
    mkdir -p /opt/uds/icons/apps
fi

install uds-explorer /opt/uds/bin
install system-file-manager.svg /opt/uds/icons/apps
install uds-explorer.desktop /usr/share/applications

update-desktop-database
ldconfig

echo "Done"

