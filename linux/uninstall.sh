#!/bin/bash
echo "Uninstalling..."

rm /opt/uds/bin/uds-explorer
rm /opt/uds/icons/apps/system-file-manager.svg
rm /usr/share/applications/uds-explorer.desktop

update-desktop-database

echo "Done" 

