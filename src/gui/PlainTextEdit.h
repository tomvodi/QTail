/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <include/FileViewInterface.h>

class PlainTextEdit : public QPlainTextEdit,
                      public FileViewInterface
{
public:
    PlainTextEdit();

    // FileViewInterface interface
public:
    FileViewInterface::Features viewFeatures() const override;
};

#endif // PLAINTEXTEDIT_H
