/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "FileFilterWidget.h"
#include "ui_FileFilterWidget.h"

FileFilterWidget::FileFilterWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::FileFilterWidget)
{
   ui->setupUi(this);
}

FileFilterWidget::~FileFilterWidget()
{
   delete ui;
}

void FileFilterWidget::setFilterGroups(const QList<FilterGroup> &groups)
{
   m_filterGroups = groups;

   setUiForFilterGroups(groups);
}

void FileFilterWidget::setActiveFilterIds(const QList<QUuid> &filterRuleIds)
{
   m_activeFilterRules = filterRuleIds;
   applyActiveFilterRules();
}

QList<QUuid> FileFilterWidget::activeFilterIds() const
{
   QList<QUuid> activeFilterRules;

   QTreeWidgetItemIterator it(ui->treeWidget);
   while (*it) {

      if ((*it)->type() == FilterGroupType) {
         ++it;
         continue;
      }

      Qt::CheckState checkedState = (*it)->checkState(0);
      if (checkedState == Qt::Checked) {
         QUuid itemId = (*it)->data(0, FilterIdDataRole).toUuid();
         if (itemId.isNull()) {
            ++it;
            continue;
         }

         activeFilterRules.append(itemId);
      }

      ++it;
   }

   return activeFilterRules;
}

void FileFilterWidget::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
   switch (item->type()) {
   case FilterGroupType:
      setCheckedStateOfAllChildItems(item, item->checkState(0));
      break;
   case FilterRuleType:
      setCheckedStateOfParentAccordingToChildItemState(item, item->checkState(0));
      break;
   }
}

void FileFilterWidget::on_applyFiltersButton_clicked()
{
   QList<QUuid> activeFilterRules = activeFilterIds();

   if (m_activeFilterRules == activeFilterRules) {
      return;
   }

   m_activeFilterRules = activeFilterRules;
   emit activeFilterIdsChanged(m_activeFilterRules);
}

void FileFilterWidget::setCheckedStateOfAllChildItems(const QTreeWidgetItem *parentItem,
                                                      Qt::CheckState state)
{
   if (parentItem->treeWidget()) {
      parentItem->treeWidget()->blockSignals(true);
   }

   for (int i = 0; i < parentItem->childCount(); ++i) {
      QTreeWidgetItem *childItem = parentItem->child(i);
      if (!childItem) {
         continue;
      }
      childItem->setCheckState(0, state);
   }

   if (parentItem->treeWidget()) {
      parentItem->treeWidget()->blockSignals(false);
   }
}

void FileFilterWidget::setCheckedStateOfParentAccordingToChildItemState(const QTreeWidgetItem *childItem,
                                                                        Qt::CheckState state)
{
   QTreeWidgetItem *parentItem = childItem->parent();
   if (!parentItem) {
      return;
   }

   Qt::CheckState parentCheckedState = Qt::Unchecked;
   bool allChildrenChecked = true;

   for (int i = 0; i < parentItem->childCount(); ++i) {
      QTreeWidgetItem *childItem = parentItem->child(i);
      if (!childItem) {
         continue;
      }
      switch (childItem->checkState(0)) {
      case Qt::Unchecked:
         allChildrenChecked = false;
         break;
      case Qt::Checked:
         parentCheckedState = Qt::PartiallyChecked;
         break;
      case Qt::PartiallyChecked:
         break;
      }
   }

   if (allChildrenChecked) {
      parentCheckedState = Qt::Checked;
   }

   if (parentItem->treeWidget()) {
      parentItem->treeWidget()->blockSignals(true);
   }

   parentItem->setCheckState(0, parentCheckedState);

   if (parentItem->treeWidget()) {
      parentItem->treeWidget()->blockSignals(false);
   }
}

void FileFilterWidget::applyActiveFilterRules()
{
   QTreeWidgetItemIterator it(ui->treeWidget);
   while (*it) {
      if ((*it)->type() == FilterGroupType) {
         ++it;
         continue;
      }

      QUuid itemId = (*it)->data(0, FilterIdDataRole).toUuid();
      if (itemId.isNull()) {
         ++it;
         continue;
      }

      if (m_activeFilterRules.contains(itemId)) {
         (*it)->setCheckState(0, Qt::Checked);
      } else {
         (*it)->setCheckState(0, Qt::Unchecked);
      }
      ++it;
   }
}

void FileFilterWidget::setUiForFilterGroups(const QList<FilterGroup> &groups)
{
   ui->treeWidget->clear();

   QList<QTreeWidgetItem *> groupItems;

   foreach (const FilterGroup &group, groups) {
      QTreeWidgetItem *groupItem = new QTreeWidgetItem(QStringList(group.name()), FilterGroupType);
      groupItem->setCheckState(0, Qt::Unchecked);

      QList<QTreeWidgetItem *> ruleItems;
      foreach (const FilterRule &rule, group.filterRules()) {
         QTreeWidgetItem *ruleItem = new QTreeWidgetItem(QStringList(rule.filter()), FilterRuleType);
         ruleItem->setCheckState(0, Qt::Unchecked);
         ruleItem->setData(0, FilterIdDataRole, rule.id());

         ruleItems.append(ruleItem);
      }
      groupItem->addChildren(ruleItems);

      groupItems.append(groupItem);
   }

   ui->treeWidget->insertTopLevelItems(0, groupItems);

   applyActiveFilterRules();
}
