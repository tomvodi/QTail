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

class PlainTextEdit : public QPlainTextEdit
{
public:
   PlainTextEdit(QWidget *parent=0);

   void setScrollEnabled(bool enabled);
   bool scrollEnabled() const;

protected:
   void scrollContentsBy(int dx, int dy);

private:
   bool m_scrollEnabled = true;
};

#endif // PLAINTEXTEDIT_H
