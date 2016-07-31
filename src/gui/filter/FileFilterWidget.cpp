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

         ruleItems.append(ruleItem);
      }
      groupItem->addChildren(ruleItems);

      groupItems.append(groupItem);
   }

   ui->treeWidget->insertTopLevelItems(0, groupItems);
}
