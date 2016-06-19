/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <include/FilterGroup.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::FilterDialog)
{
   ui->setupUi(this);

   ui->filterGroupComboBox->addItem(tr("Default group"));
}

FilterDialog::~FilterDialog()
{
   delete ui;
}

void FilterDialog::setFilterGroups(const QList<FilterGroup> &filterGrops)
{
   ui->filterGroupComboBox->clear();
   foreach (const FilterGroup &group, filterGrops) {
      ui->filterGroupComboBox->addItem(group.name());
   }
}
