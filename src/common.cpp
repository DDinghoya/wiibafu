/***************************************************************************
 *   Copyright (C) 2010 DynUp                                              *
 *   dynup@ymail.com | wiibafu.codeplex.com                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "common.h"

Common::Common(QObject *parent) : QObject(parent) {

}

void Common::getGameCover(QString gameID) {
    QUrl url(QString("http://wiitdb.com/wiitdb/artwork/cover3D/EN/%1.png").arg(gameID));
    http = new QHttp(this);
    http->setHost(url.host());

    connect(http, SIGNAL(requestFinished(int, bool)), this, SLOT(loadGameCoverFinished(int, bool)));

    http->get(url.path());
}

void Common::loadGameCoverFinished(int, bool error) {
    if (!error) {
        QImage *image = new QImage();
        image->loadFromData(http->readAll());

        emit newGameCover(image);
    }
}
