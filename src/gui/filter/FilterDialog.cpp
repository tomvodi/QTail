/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QInputDialog>
#include <QMessageBox>

#include <include/FilterRule.h>
#include <include/FilterGroup.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::FilterDialog)
{
   ui->setupUi(this);

   addDefaultGroup();
}

FilterDialog::~FilterDialog()
{
   delete ui;
}

void FilterDialog::setFilterGroups(const QList<FilterGroup> &groups)
{
   ui->filterGroupComboBox->clear();

   // Initially add at least a default group
   if (groups.isEmpty()) {
      addDefaultGroup();
      emit filterGroupsChanged(filterGroups());
      return;
   }

   foreach (const FilterGroup &group, groups) {
      addGroup(group);
   }

   if (ui->filterGroupComboBox->count()) {
      ui->filterGroupComboBox->setCurrentIndex(0);
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
   setCurrentFilterGroupDataFromGui();
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

   addGroup(FilterGroup(groupName));
   checkForEnabledDeleteFilterGroupButton();
}

void FilterDialog::on_addFilterButton_clicked()
{
   FilterRule filterRule(ui->regexLineEdit->text());
   filterRule.setCaseSensitivity(ui->caseSensitiveCheckBox->isChecked() ?
                                    Qt::CaseSensitive : Qt::CaseInsensitive);

   addFilterRuleItem(filterRule);
   setCurrentFilterGroupDataFromGui();
}

void FilterDialog::on_deleteGroupButton_clicked()
{
   int currentGroupIndex = ui->filterGroupComboBox->currentIndex();
   if (currentGroupIndex == -1) {
      return;
   }

   QString currentGroupname = ui->filterGroupComboBox->currentText();
   int result = QMessageBox::question(this, tr("Delete group?"),
                                      tr("Do you want to delete filter group %1?").arg(currentGroupname),
                                      QMessageBox::Cancel | QMessageBox::Default, QMessageBox::Ok);
   if (result == QMessageBox::Ok) {
      ui->filterGroupComboBox->removeItem(currentGroupIndex);
      emit filterGroupsChanged(filterGroups());
      checkForEnabledDeleteFilterGroupButton();
   }
}

void FilterDialog::on_regexLineEdit_editingFinished()
{
   QListWidgetItem *currentItem = ui->filtersListWidget->currentItem();
   if (!currentItem) {
      return;
   }

   currentItem->setText(ui->regexLineEdit->text());
}

void FilterDialog::on_caseSensitiveCheckBox_toggled(bool checked)
{
   QListWidgetItem *currentItem = ui->filtersListWidget->currentItem();
   if (!currentItem) {
      return;
   }

   currentItem->setData(CaseSensitiveDataRole, checked);
}

void FilterDialog::on_filtersListWidget_itemChanged(QListWidgetItem *item)
{
   setCurrentFilterGroupDataFromGui();
   setEditWidgetsContentForCurrentFilterItem();
}

void FilterDialog::on_filtersListWidget_itemClicked(QListWidgetItem *item)
{
   setEditWidgetsContentForCurrentFilterItem();
}

void FilterDialog::on_filterGroupComboBox_currentIndexChanged(int index)
{
   FilterGroup group = ui->filterGroupComboBox->currentData().value<FilterGroup>();

   setFilterRules(group.filterRules());

   setEditWidgetsContentForCurrentFilterItem();
}

void FilterDialog::on_deleteFilterButton_clicked()
{
   QListWidgetItem *item = ui->filtersListWidget->currentItem();
   if (!item) {
      return;
   }

   delete item;
}

void FilterDialog::on_buttonBox_clicked(QAbstractButton *button)
{
   QDialogButtonBox::StandardButton standardButton = ui->buttonBox->standardButton(button);
   if (standardButton == QDialogButtonBox::Apply ||
       standardButton == QDialogButtonBox::Ok) {
      emit filterGroupsChanged(filterGroups());
   }
}

void FilterDialog::addDefaultGroup()
{
   addGroup(FilterGroup(tr("Default group")));
}

QList<FilterGroup> FilterDialog::filterGroups() const
{
   QList<FilterGroup> groups;

   for (int i = 0; i < ui->filterGroupComboBox->count(); ++i) {
      QVariant groupData = ui->filterGroupComboBox->itemData(i);
      if (!groupData.canConvert<FilterGroup>()) {
         continue;
      }

      FilterGroup group = groupData.value<FilterGroup>();
      groups << group;
   }

   return groups;
}

void FilterDialog::addGroup(const FilterGroup &group)
{
   QVariant groupData = QVariant::fromValue<FilterGroup>(group);
   ui->filterGroupComboBox->addItem(group.name(), groupData);
   ui->filterGroupComboBox->setCurrentText(group.name());
}

void FilterDialog::setFilterRules(const QList<FilterRule> &filters)
{
   ui->filtersListWidget->clear();

   foreach (const FilterRule &filterRule, filters) {
      addFilterRuleItem(filterRule);
   }
}

void FilterDialog::addFilterRuleItem(const FilterRule &filterRule)
{
   QListWidgetItem *newItem = new QListWidgetItem(filterRule.filter());
   newItem->setData(CaseSensitiveDataRole, (filterRule.caseSensitivity() == Qt::CaseSensitive));
   newItem->setFlags(newItem->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
   newItem->setCheckState(filterRule.isActive() ? Qt::Checked : Qt::Unchecked);

   ui->filtersListWidget->addItem(newItem);
   ui->filtersListWidget->setCurrentItem(newItem);
}

/*!
 * \brief FilterDialog::setCurrentFilterGroupDataFromGui
 * Takes the current group data from gui (group name, filter rules list) and
 * stores into the current group list item as data.
 */
void FilterDialog::setCurrentFilterGroupDataFromGui()
{
   QList<FilterRule> filterRules;
   for (int i = 0; i < ui->filtersListWidget->count(); ++i) {
      QListWidgetItem *item = ui->filtersListWidget->item(i);
      if (!item) {
         continue;
      }

      FilterRule rule;
      bool caseSensitive = item->data(CaseSensitiveDataRole).toBool();
      rule.setCaseSensitivity(caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
      rule.setFilter(item->text());
      rule.setActive(item->checkState() == Qt::Checked ? true : false);
      filterRules << rule;
   }

   int currentGroupIndex = ui->filterGroupComboBox->currentIndex();
   if (currentGroupIndex == -1) {
      return;
   }

   QVariant groupData = ui->filterGroupComboBox->currentData();
   FilterGroup filterGroup = groupData.value<FilterGroup>();
   filterGroup.setName(ui->filterGroupComboBox->currentText());
   filterGroup.setFilterRules(filterRules);
   ui->filterGroupComboBox->setItemData(currentGroupIndex, QVariant::fromValue<FilterGroup>(filterGroup));
}

void FilterDialog::setEditWidgetsContentForCurrentFilterItem()
{
   QListWidgetItem *currentItem = ui->filtersListWidget->currentItem();
   if (!currentItem) {
      return;
   }

   ui->regexLineEdit->setText(currentItem->text());
}

void FilterDialog::checkForEnabledDeleteFilterGroupButton()
{
   if (ui->filterGroupComboBox->count() <= 1) {
      ui->deleteGroupButton->setEnabled(false);
   } else {
      ui->deleteGroupButton->setEnabled(true);
   }
}
