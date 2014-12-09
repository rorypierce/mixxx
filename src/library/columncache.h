#ifndef COLUMNCACHE_H
#define COLUMNCACHE_H

#include <QMap>
#include <QStringList>

// Caches the index of frequently used columns and provides a lookup-table of
// column name to index.
class ColumnCache {
  public:

    // DO NOT insert enums into the middle of this list or it will break saved
    // header information.  Instead, always add to the bottom (leaving
    // NUM_COLUMNS as the very last item).
    enum Column {
        COLUMN_LIBRARYTABLE_ID,
        COLUMN_LIBRARYTABLE_ARTIST,
        COLUMN_LIBRARYTABLE_TITLE,
        COLUMN_LIBRARYTABLE_ALBUM,
        COLUMN_LIBRARYTABLE_ALBUMARTIST,
        COLUMN_LIBRARYTABLE_YEAR,
        COLUMN_LIBRARYTABLE_GENRE,
        COLUMN_LIBRARYTABLE_COMPOSER,
        COLUMN_LIBRARYTABLE_GROUPING,
        COLUMN_LIBRARYTABLE_TRACKNUMBER,
        COLUMN_LIBRARYTABLE_FILETYPE,
        COLUMN_LIBRARYTABLE_LOCATION,
        COLUMN_LIBRARYTABLE_COMMENT,
        COLUMN_LIBRARYTABLE_DURATION,
        COLUMN_LIBRARYTABLE_BITRATE,
        COLUMN_LIBRARYTABLE_BPM,
        COLUMN_LIBRARYTABLE_REPLAYGAIN,
        COLUMN_LIBRARYTABLE_CUEPOINT,
        COLUMN_LIBRARYTABLE_URL,
        COLUMN_LIBRARYTABLE_SAMPLERATE,
        COLUMN_LIBRARYTABLE_WAVESUMMARYHEX,
        COLUMN_LIBRARYTABLE_CHANNELS,
        COLUMN_LIBRARYTABLE_MIXXXDELETED,
        COLUMN_LIBRARYTABLE_DATETIMEADDED,
        COLUMN_LIBRARYTABLE_HEADERPARSED,
        COLUMN_LIBRARYTABLE_TIMESPLAYED,
        COLUMN_LIBRARYTABLE_PLAYED,
        COLUMN_LIBRARYTABLE_RATING,
        COLUMN_LIBRARYTABLE_KEY,
        COLUMN_LIBRARYTABLE_KEY_ID,
        COLUMN_LIBRARYTABLE_BPM_LOCK,
        COLUMN_LIBRARYTABLE_PREVIEW,
        COLUMN_LIBRARYTABLE_COVERART,
        COLUMN_LIBRARYTABLE_COVERART_SOURCE,
        COLUMN_LIBRARYTABLE_COVERART_TYPE,
        COLUMN_LIBRARYTABLE_COVERART_LOCATION,
        COLUMN_LIBRARYTABLE_COVERART_HASH,

        COLUMN_TRACKLOCATIONSTABLE_FSDELETED,

        COLUMN_PLAYLISTTRACKSTABLE_TRACKID,
        COLUMN_PLAYLISTTRACKSTABLE_POSITION,
        COLUMN_PLAYLISTTRACKSTABLE_PLAYLISTID,
        COLUMN_PLAYLISTTRACKSTABLE_LOCATION,
        COLUMN_PLAYLISTTRACKSTABLE_ARTIST,
        COLUMN_PLAYLISTTRACKSTABLE_TITLE,
        COLUMN_PLAYLISTTRACKSTABLE_DATETIMEADDED,

        COLUMN_CRATETRACKSTABLE_TRACKID,
        COLUMN_CRATETRACKSTABLE_CRATEID,

        // NUM_COLUMNS should always be the last item.
        NUM_COLUMNS
    };

    ColumnCache() { }
    ColumnCache(const QStringList& columns) {
        setColumns(columns);
    }

    void setColumns(const QStringList& columns);

    inline int fieldIndex(Column column) const {
        if (column < 0 || column >= NUM_COLUMNS) {
            return -1;
        }
        return m_columnIndexByEnum[column];
    }

    inline int fieldIndex(const QString& columnName) const {
        return m_columnIndexByName.value(columnName, -1);
    }

    QMap<QString, int> m_columnIndexByName;
    int m_columnIndexByEnum[NUM_COLUMNS];
};

#endif /* COLUMNCACHE_H */
