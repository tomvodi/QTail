/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnDefinitionDialog.h"
#include "ui_ColumnDefinitionDialog.h"

ColumnDefinitionDialog::ColumnDefinitionDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::ColumnDefinitionDialog)
{
   ui->setupUi(this);
}

ColumnDefinitionDialog::~ColumnDefinitionDialog()
{
   delete ui;
}

ColumnFactory ColumnDefinitionDialog::columnFactory() const
{
   return m_columnFactory;
}

void ColumnDefinitionDialog::setColumnFactory(const ColumnFactory &columnFactory)
{
   m_columnFactory = columnFactory;
}
