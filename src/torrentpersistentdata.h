/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef TORRENTPERSISTENTDATA_H
#define TORRENTPERSISTENTDATA_H

#include <QVariant>
#include <QDateTime>
#include <libtorrent/version.hpp>
#include <libtorrent/magnet_uri.hpp>
#include "qtorrenthandle.h"
#include "misc.h"
#include <vector>
#include "qinisettings.h"
#include <QHash>

class TorrentTempData {
public:
  static bool hasTempData(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    return all_data.contains(hash);
  }

  static void deleteTempData(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    if(all_data.contains(hash)) {
      all_data.remove(hash);
      settings.setValue("torrents-tmp", all_data);
    }
  }

  static void setFilesPriority(QString hash,  const std::vector<int> &pp) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    std::vector<int>::const_iterator pp_it = pp.begin();
    QStringList pieces_priority;
    while(pp_it != pp.end()) {
      pieces_priority << QString::number(*pp_it);
      pp_it++;
    }
    data["files_priority"] = pieces_priority;
    all_data[hash] = data;
    settings.setValue("torrents-tmp", all_data);
  }

  static void setFilesPath(QString hash, const QStringList &path_list) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["files_path"] = path_list;
    all_data[hash] = data;
    settings.setValue("torrents-tmp", all_data);
  }

  static void setSavePath(QString hash, QString save_path) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["save_path"] = save_path;
    all_data[hash] = data;
    settings.setValue("torrents-tmp", all_data);
  }

  static void setLabel(QString hash, QString label) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    qDebug("Saving label %s to tmp data", label.toLocal8Bit().data());
    data["label"] = label;
    all_data[hash] = data;
    settings.setValue("torrents-tmp", all_data);
  }

  static void setSequential(QString hash, bool sequential) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["sequential"] = sequential;
    all_data[hash] = data;
    settings.setValue("torrents-tmp", all_data);
  }

  static bool isSequential(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    if(data.contains("sequential"))
      return data["sequential"].toBool();
    return false;

  }

#if LIBTORRENT_VERSION_MINOR > 14
  static void setSeedingMode(QString hash,bool seed){
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["seeding"] = seed;
    all_data[hash] = data;
    settings.setValue("torrents-tmp", all_data);
  }

  static bool isSeedingMode(QString hash){
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    if(data.contains("seeding"))
      return data["seeding"].toBool();
    return false;
  }
#endif

  static QString getSavePath(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    if(data.contains("save_path"))
      return data["save_path"].toString();
    qDebug("Warning Temp::getSavePath returns null string!");
    return QString::null;
  }

  static QStringList getFilesPath(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    if(data.contains("files_path"))
      return data["files_path"].toStringList();
    return QStringList();
  }

  static QString getLabel(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    qDebug("Got label %s from tmp data", data.value("label", "").toString().toLocal8Bit().data());
    return data.value("label", "").toString();
  }

  static std::vector<int> getFilesPriority(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents-tmp", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    std::vector<int> fp;
    if(data.contains("files_priority")) {
      QList<int> list_var = misc::intListfromStringList(data["files_priority"].toStringList());
      foreach(int var, list_var) {
        fp.push_back(var);
      }
    }
    return fp;
  }
};

class TorrentPersistentData {
public:

  static bool isKnownTorrent(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    return all_data.contains(hash);
  }

  static QStringList knownTorrents() {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    return all_data.keys();
  }

  static void setAddedDate(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    if(!data.contains("add_date")) {
      data.insert("add_date", QDateTime::currentDateTime());
      all_data[hash] = data;
      settings.setValue("torrents", all_data);
    }
  }

  static QDateTime getAddedDate(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    QDateTime dt = data.value("add_date", QDateTime()).toDateTime();
    if(!dt.isValid()) {
      setAddedDate(hash);
      dt = QDateTime::currentDateTime();
    }
    return dt;
  }

  static void setErrorState(QString hash, bool has_error) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data.insert("has_error", has_error);
    all_data[hash] = data;
    settings.setValue("torrents", all_data);
  }

  static bool hasError(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("has_error", false).toBool();
  }

  static void setRootFolder(QString hash, QString root_folder) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data.insert("root_folder", root_folder);
    all_data[hash] = data;
    settings.setValue("torrents", all_data);
  }

  static QString getRootFolder(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("root_folder", QString()).toString();
  }

  static void setPreviousSavePath(QString hash, QString previous_path) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data.insert("previous_path", previous_path);
    all_data[hash] = data;
    settings.setValue("torrents", all_data);
  }

  static QString getPreviousPath(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("previous_path", QString()).toString();
  }
  
  static void saveSeedDate(const QTorrentHandle &h) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[h.hash()].toHash();
    if(h.is_seed())
      data.insert("seed_date", QDateTime::currentDateTime());
    else
      data.insert("seed_date", QDateTime());
    all_data[h.hash()] = data;
    settings.setValue("torrents", all_data);
  }

  static QDateTime getSeedDate(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("seed_date", QDateTime()).toDateTime();
  }

  static void deletePersistentData(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    if(all_data.contains(hash)) {
      all_data.remove(hash);
      settings.setValue("torrents", all_data);
    }
  }

  static void saveTorrentPersistentData(const QTorrentHandle &h, bool is_magnet = false) {
    Q_ASSERT(h.is_valid());
    qDebug("Saving persistent data for %s", h.hash().toLocal8Bit().data());
    // First, remove temp data
    TorrentTempData::deleteTempData(h.hash());
    Q_ASSERT(!TorrentTempData::hasTempData(h.hash()));
    // Save persistent data
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data;
    data["is_magnet"] = is_magnet;
    if(is_magnet) {
      data["magnet_uri"] = misc::toQString(make_magnet_uri(h.get_torrent_handle()));
    }
    data["seed"] = h.is_seed();
    data["priority"] = h.queue_position();
    data["save_path"] = h.save_path();
    // Save data
    all_data[h.hash()] = data;
    settings.setValue("torrents", all_data);
    qDebug("TorrentPersistentData: Saving save_path %s, hash: %s", h.save_path().toLocal8Bit().data(), h.hash().toLocal8Bit().data());
    // Set Added date
    setAddedDate(h.hash());
  }

  // Setters

  static void saveSavePath(QString hash, QString save_path) {
    Q_ASSERT(!hash.isEmpty());
    qDebug("TorrentPersistentData::saveSavePath(%s)", qPrintable(save_path));
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["save_path"] = save_path;
    all_data[hash] = data;
    settings.setValue("torrents", all_data);
    qDebug("TorrentPersistentData: Saving save_path: %s, hash: %s", save_path.toLocal8Bit().data(), hash.toLocal8Bit().data());
  }

  static void saveLabel(QString hash, QString label) {
    Q_ASSERT(!hash.isEmpty());
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["label"] = label;
    all_data[hash] = data;
    settings.setValue("torrents", all_data);
  }

  static void saveName(QString hash, QString name) {
    Q_ASSERT(!hash.isEmpty());
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    data["name"] = name;
    all_data[hash] = data;
    settings.setValue("torrents", all_data);
  }

  static void savePriority(const QTorrentHandle &h) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[h.hash()].toHash();
    data["priority"] = h.queue_position();
    all_data[h.hash()] = data;
    settings.setValue("torrents", all_data);
  }

  static void saveSeedStatus(const QTorrentHandle &h) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[h.hash()].toHash();
    bool was_seed = data.value("seed", false).toBool();
    if(was_seed != h.is_seed()) {
      data["seed"] = !was_seed;
      all_data[h.hash()] = data;
      settings.setValue("torrents", all_data);
      if(!was_seed) {
        // Save completion date
        saveSeedDate(h);
      }
    }
  }

  // Getters
  static QString getSavePath(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    //qDebug("TorrentPersistentData: getSavePath %s", data["save_path"].toString().toLocal8Bit().data());
    return data["save_path"].toString();
  }

  static QString getLabel(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("label", "").toString();
  }

  static QString getName(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("name", "").toString();
  }

  static int getPriority(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data["priority"].toInt();
  }

  static bool isSeed(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data.value("seed", false).toBool();
  }

  static bool isMagnet(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    return data["is_magnet"].toBool();
  }

  static QString getMagnetUri(QString hash) {
    QIniSettings settings(QString::fromUtf8("qBittorrent"), QString::fromUtf8("qBittorrent-resume"));
    QHash<QString, QVariant> all_data = settings.value("torrents", QHash<QString, QVariant>()).toHash();
    QHash<QString, QVariant> data = all_data[hash].toHash();
    Q_ASSERT(data["is_magnet"].toBool());
    return data["magnet_uri"].toString();
  }

};

#endif // TORRENTPERSISTENTDATA_H
