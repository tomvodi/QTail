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
   QString newText = QInputDialog::getText(this, tr("Rename current group"), tr("New name"),
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

void FilterDialog::on_addGroupButton_clicked()
{
   bool ok;
   QString groupName = QInputDialog::getText(this, tr("Add new group"), tr("Group name"),
                                           QLineEdit::Normal, "",
                                           &ok);

   if (!ok || groupName.isEmpty()) {
      return;
   }

   addGroupWithName(groupName);
}

void FilterDialog::on_addFilterButton_clicked()
{
   QListWidgetItem *newItem = new QListWidgetItem(ui->regexLineEdit->text());
   newItem->setData(CaseSensitiveRole, ui->caseSensitiveCheckBox->isChecked());
   newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);

   ui->filtersListWidget->addItem(newItem);
   ui->filtersListWidget->setCurrentItem(newItem);
}

void FilterDialog::on_regexLineEdit_textChanged(const QString &text)
{
   QListWidgetItem *currentItem = ui->filtersListWidget->currentItem();
   if (!currentItem) {
      return;
   }

   currentItem->setText(text);
}

void FilterDialog::on_caseSensitiveCheckBox_toggled(bool checked)
{
   QListWidgetItem *currentItem = ui->filtersListWidget->currentItem();
   if (!currentItem) {
      return;
   }

   currentItem->setData(CaseSensitiveRole, checked);
}

void FilterDialog::on_filtersListWidget_itemChanged(QListWidgetItem *item)
{
   if (item == ui->filtersListWidget->currentItem()) {
      ui->regexLineEdit->setText(item->text());
   }
}

void FilterDialog::addGroupWithName(const QString &groupName)
{
   ui->filterGroupComboBox->addItem(groupName);
   ui->filterGroupComboBox->setCurrentText(groupName);
}
