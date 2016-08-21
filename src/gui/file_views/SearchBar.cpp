/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "SearchBar.h"
#include "ui_SearchBar.h"

SearchBar::SearchBar(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::SearchBar)
{
   ui->setupUi(this);
   setResultNumberAndCount(0, 0);
   createConnections();
}

SearchBar::~SearchBar()
{
   delete ui;
}

int SearchBar::resultNumber() const
{
   return ui->resultLabel->text().toInt();
}

void SearchBar::setResultNumber(int number)
{
   ui->resultLabel->setText(QString::number(number));
}

int SearchBar::resultCount() const
{
   return ui->resultCountLabel->text().toInt();
}

void SearchBar::setResultCount(int count)
{
   ui->resultCountLabel->setText(QString::number(count));
}

void SearchBar::setResultNumberAndCount(int number, int count)
{
   setResultNumber(number);
   setResultCount(count);
}

void SearchBar::createConnections()
{
   connect(ui->searchButton, &QToolButton::clicked,
           [this] {
      emit searchTriggered(ui->searchLineEdit->text(),
                           (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
   });
}
