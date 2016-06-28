/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <include/FilterGroup.h>

#include <QInputDialog>

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

void FilterDialog::on_renameGroupButton_clicked()
{
   bool ok;
   QString newText = QInputDialog::getText(this, tr("Rename current rules"), tr("New name"),
                                           QLineEdit::Normal, ui->filterGroupComboBox->currentText(),
                                           &ok);

   if (!ok || newText.isEmpty()) {
      return;
   }

   setCurrentGroupName(newText);
}

void FilterDialog::setCurrentGroupName(const QString &newName)
{
   int currentIndex = ui->filterGroupComboBox->currentIndex();
   if (currentIndex == -1) {
      return;
   }

   ui->filterGroupComboBox->setItemData(currentIndex, newName, Qt::DisplayRole);
}
