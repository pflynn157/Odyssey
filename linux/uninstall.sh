#!/bin/bash
echo "Uninstalling..."

rm /usr/local/bin/odyssey
rm /usr/local/bin/odyt
rm /usr/share/icons/hicolor/scalable/apps/odyssey.svg
rm /usr/share/applications/odyssey.desktop

update-desktop-database

echo "Done" 

