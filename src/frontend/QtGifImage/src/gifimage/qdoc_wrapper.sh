#!/bin/sh
QT_VERSION=0.1.0
export QT_VERSION
QT_VER=0.1
export QT_VER
QT_VERSION_TAG=010
export QT_VERSION_TAG
QT_INSTALL_DOCS=/usr/share/qt5/doc
export QT_INSTALL_DOCS
BUILDDIR=/home/jexwerqwez/Documents/CPP4_3DViewer_v2.0-1/src/QtGifImage/src/gifimage
export BUILDDIR
exec /usr/lib/qt5/bin/qdoc "$@"
