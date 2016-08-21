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

   int resultNumber() const;
   void setResultNumber(int number);

   int resultCount() const;
   void setResultCount(int count);

   void setResultNumberAndCount(int number, int count);

signals:
   void searchTriggered(const QString &text, Qt::CaseSensitivity caseSensitive);
   void searchCleared();
   void gotoNextResult();
   void gotoPreviousResult();
   void gotoFirstResult();
   void gotoLastResult();

private slots:
   void textEdited(const QString &text);

private:
   void createConnections();
   Ui::SearchBar *ui;
};

#endif // SEARCHBAR_H
