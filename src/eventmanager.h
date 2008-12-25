/*
 *   Copyright (C) 2007 by Ishan Arora & Christophe Dumez
 *   <ishan@qbittorrent.org>, <chris@qbittorrent.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "qtorrenthandle.h"
#include <QHash>
#include <QVariant>

struct bittorrent;

class EventManager : public QObject
{
	Q_OBJECT
	private:
		QHash<QString, QVariantMap> event_list;
		bittorrent* BTSession;

	protected:
		void update(QVariantMap event);

	public:
		EventManager(QObject *parent, bittorrent* BTSession);
                QList<QVariantMap> getEventList() const;

	public slots:
		void addedTorrent(QTorrentHandle& h);
		void deletedTorrent(QString hash);
		void modifiedTorrent(QTorrentHandle h);
};

#endif
