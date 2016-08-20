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
}

SearchBar::~SearchBar()
{
   delete ui;
}
