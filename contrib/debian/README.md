
Debian
====================
This directory contains files used to package e4coind/e4coin-qt
for Debian-based Linux systems. If you compile e4coind/e4coin-qt yourself, there are some useful files here.

## e4coin: URI support ##


e4coin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install e4coin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your e4coin-qt binary to `/usr/bin`
and the `../../share/pixmaps/e4coin128.png` to `/usr/share/pixmaps`

e4coin-qt.protocol (KDE)

