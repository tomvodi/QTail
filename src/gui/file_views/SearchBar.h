/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QFrame>

namespace Ui {
class SearchBar;
}

class SearchBar : public QFrame
{
   Q_OBJECT

public:
   explicit SearchBar(QWidget *parent = 0);
   ~SearchBar();

private:
   Ui::SearchBar *ui;
};

#endif // SEARCHBAR_H
