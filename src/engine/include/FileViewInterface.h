/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEVIEWINTERFACE_H
#define FILEVIEWINTERFACE_H

enum class FileState {
    FileError,
    FileInSync,
    FileHasNewLines
};

/*!
 * \brief The FileViewInterface class
 *
 */
class FileViewInterface
{
public:
    FileViewInterface() {}
    virtual ~FileViewInterface() {}

    virtual void setFileState(FileState state) = 0;
};

#endif // FILEVIEWINTERFACE_H
