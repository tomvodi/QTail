/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PlainTextEdit.h"

PlainTextEdit::PlainTextEdit()
{
    setReadOnly(true);
}

FileViewInterface::Features PlainTextEdit::viewFeatures() const
{
   return FileViewInterface::HasTextView;
}
