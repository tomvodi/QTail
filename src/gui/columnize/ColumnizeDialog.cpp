/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnizeDialog.h"
#include "ui_ColumnizeDialog.h"

ColumnizeDialog::ColumnizeDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::ColumnizeDialog)
{
   ui->setupUi(this);
}

ColumnizeDialog::~ColumnizeDialog()
{
   delete ui;
}
