/* This file is part of the Screenie project.
   Screenie is a fancy screenshot composer.

   Copyright (C) 2008 Ariya Hidayat <ariya.hidayat@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <QtCore/QtGlobal>

#include "ScreenieApplication.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Resources);

    // workaround for http://bugreports.qt.nokia.com/browse/QTBUG-15663: use
    // the "raster" paint engine on affected OSes (Mac and Linux, Qt 4.7.1).
    // Note that the command line argument -graphicssystem still takes precedence (which is good)
// #if defined Q_OS_MAC || defined Q_OS_LINUX
#ifdef Q_OS_LINUX
    // Doh! This uncovers another Qt bug, at least on Mac with Qt 4.7.1
    // (Linux with Qt 4.7.0 seems to work though): the selection borders in the
    // QGraphicsView are not always properly drawn/updated with multiple
    // selection (CTRL + left click): the first item is visually selected
    // properly, the 2nd not, the 3rd yes (also rendering the 2nd item
    // properply as selected, the 4th no, the 5th yes (again rendering all
    // selected items so far correct)... (note that the model itself is always
    // marked selected properly).
    // UPDATE: Cannot reproduce the selection problem anymore. However the
    // widgets are sometimes painted "upside down" on Mac with Raster graphics engine,
    // see http://bugreports.qt.nokia.com/browse/QTBUG-16590
    //
    // So for now we live with the graphical artifact when rotating images,
    // which is less serious than broken selection.
    // Setting the QGraphicsView to OpenGL would probably also help (no artifacts
    // there either, selection is hopefully fine).
    QApplication::setGraphicsSystem("raster");
#endif
    ScreenieApplication app(argc, argv);
    app.show();

    return app.exec();
}

