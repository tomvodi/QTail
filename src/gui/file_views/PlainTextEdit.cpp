/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PlainTextEdit.h"

PlainTextEdit::PlainTextEdit(QWidget *parent)
   : QPlainTextEdit(parent)
{
   setCenterOnScroll(true);
   setReadOnly(true);
}
