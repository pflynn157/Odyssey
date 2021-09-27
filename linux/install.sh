#!/bin/bash
echo "Installing..."

install odyssey /usr/local/bin
install odyt /usr/local/bin
install odyssey.svg /usr/share/icons/hicolor/scalable/apps
install odyssey.desktop /usr/share/applications

update-desktop-database
ldconfig

echo "Done"

