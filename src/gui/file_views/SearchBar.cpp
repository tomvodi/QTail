/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QIcon>

#include "SearchBar.h"
#include "ui_SearchBar.h"

SearchBar::SearchBar(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::SearchBar)
{
   ui->setupUi(this);
   initActions();
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

void SearchBar::startSearch(const QString &text)
{
   ui->searchLineEdit->setText(text);
   on_searchButton_clicked();
}

void SearchBar::textEdited(const QString &text)
{
   if (text.isEmpty()) {
      emit searchCleared();
   }
}

void SearchBar::on_searchButton_clicked()
{
   emit searchTriggered(ui->searchLineEdit->text(),
                        (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

void SearchBar::on_nextResultButton_clicked()
{
   emit gotoNextResult();
}

void SearchBar::on_previousResultButton_clicked()
{
   emit gotoPreviousResult();
}

void SearchBar::createConnections()
{
   connect(ui->firstResultButton, &QToolButton::clicked,
           this, &SearchBar::gotoFirstResult);
   connect(ui->lastResultButton, &QToolButton::clicked,
           this, &SearchBar::gotoLastResult);
   connect(ui->searchLineEdit, &QLineEdit::textEdited,
           this, &SearchBar::textEdited);
}

void SearchBar::initActions()
{
   // Find next
   QKeySequence findNextShortcut(QKeySequence::FindNext);
   QAction *findNextAction = new QAction(QIcon("://resources/icons/actions/go-down.png"),
                                       tr("Go to next result %1").arg(findNextShortcut.toString()),
                                       this);
   findNextAction->setShortcut(findNextShortcut);
   ui->nextResultButton->setDefaultAction(findNextAction);
   connect(findNextAction, &QAction::triggered,
           this, &SearchBar::on_nextResultButton_clicked);

   // Find previous
   QKeySequence findPreviousShortcut(QKeySequence::FindPrevious);
   QAction *findPreviousAction = new QAction(QIcon("://resources/icons/actions/go-up.png"),
                                       tr("Go to previous result %1").arg(findPreviousShortcut.toString()),
                                       this);
   findPreviousAction->setShortcut(findPreviousShortcut);
   ui->previousResultButton->setDefaultAction(findPreviousAction);
   connect(findPreviousAction, &QAction::triggered,
           this, &SearchBar::on_previousResultButton_clicked);
}
