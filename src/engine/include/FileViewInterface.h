/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEVIEWINTERFACE_H
#define FILEVIEWINTERFACE_H

#include <QFlags>
#include <QString>
#include <QStringList>

enum class FileState {
    FileError,   //! File doesn't exist
    FileInSync,  //! File is in sync with UI, nothing new to see
    FileHasChanged  //! File has new unread lines
};

/*!
 * \brief The FileViewInterface class
 *  The FileViewInterface is an base class for a general file view.
 */
class FileViewInterface
{
public:
    enum Feature {
       NoFeature = 0x00,
       HasTextView = 0x01,
       HasStateView = 0x02
    };
    Q_DECLARE_FLAGS(Features, Feature)

    FileViewInterface() {}
    virtual ~FileViewInterface() {}

    virtual FileViewInterface::Features viewFeatures() const;

    // FileState feature methods
    virtual void setFileState(FileState state);

    // TextView feature methods
    virtual void appendLine(const QString &line);
    virtual void appendLines(const QStringList &lines);
    virtual void clearTextView();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(FileViewInterface::Features)

#endif // FILEVIEWINTERFACE_H
