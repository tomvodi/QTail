/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QInputDialog>

#include <include/FilterRule.h>
#include <include/FilterGroup.h>

#include "FilterDialog.h"
#include "ui_FilterDialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::FilterDialog)
{
   ui->setupUi(this);

   addGroup(FilterGroup(tr("Default group")));
}

FilterDialog::~FilterDialog()
{
   delete ui;
}

void FilterDialog::setFilterGroups(const QList<FilterGroup> &filterGrops)
{
   ui->filterGroupComboBox->clear();
   foreach (const FilterGroup &group, filterGrops) {
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
}

void FilterDialog::on_addFilterButton_clicked()
{
   FilterRule filterRule(ui->regexLineEdit->text());
   filterRule.setCaseSensitivity(ui->caseSensitiveCheckBox->isChecked() ?
                                    Qt::CaseSensitive : Qt::CaseInsensitive);

   addFilterRuleItem(filterRule);
   setFilterRulesInGroupDataFromFilterRuleList();
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
   if (item == ui->filtersListWidget->currentItem()) {
      ui->regexLineEdit->setText(item->text());
   }
   setFilterRulesInGroupDataFromFilterRuleList();
}

void FilterDialog::on_filterGroupComboBox_currentIndexChanged(int index)
{
   FilterGroup group = ui->filterGroupComboBox->currentData().value<FilterGroup>();

   setFilterRules(group.filterRules());
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
   newItem->setCheckState(filterRule.active() ? Qt::Checked : Qt::Unchecked);

   ui->filtersListWidget->addItem(newItem);
   ui->filtersListWidget->setCurrentItem(newItem);
}

void FilterDialog::setFilterRulesInGroupDataFromFilterRuleList()
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
   filterGroup.setFilterRules(filterRules);
   ui->filterGroupComboBox->setItemData(currentGroupIndex, QVariant::fromValue<FilterGroup>(filterGroup));
}
