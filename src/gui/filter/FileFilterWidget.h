/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEFILTERWIDGET_H
#define FILEFILTERWIDGET_H

#include <QFrame>

#include <include/FilterGroup.h>

namespace Ui {
class FileFilterWidget;
}
class QTreeWidgetItem;

/*!
 * \brief The FileFilterWidget class
 * Apart from the FilterDialog which lets add/edit/delete filters and filter groups,
 * this widget shows the activated filters for a specific open file.
 */
class FileFilterWidget : public QFrame
{
   Q_OBJECT
   friend class FileFilterWidgetTest;

public:
   explicit FileFilterWidget(QWidget *parent = 0);
   ~FileFilterWidget();

   void setFilterGroups(const QList<FilterGroup> &groups);

   void setActiveFilterIds(const QList<QUuid> &filterRuleIds);
   QList<QUuid> activeFilterIds() const;
   QList<FilterRule> activeFilterRules() const;

signals:
   void activeFilterRulesChanged(const QList<FilterRule>  &filterRules);

private slots:
   void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);
   void on_applyFiltersButton_clicked();

private:
   enum TreeItemType {
      FilterGroupType,
      FilterRuleType
   };
   static const int FilterIdDataRole = Qt::UserRole + 1;
   void setUiForFilterGroups(const QList<FilterGroup> &groups);
   void setCheckedStateOfAllChildItems(const QTreeWidgetItem *parentItem, Qt::CheckState state);
   void setCheckedStateOfParentAccordingToChildItemState(const QTreeWidgetItem *childItem,
                                                         Qt::CheckState state);
   void applyActiveFilterIdsToTreeView(const QList<QUuid> &filterRuleIds);
   Ui::FileFilterWidget *ui;
   QList<FilterGroup> m_filterGroups;
   QList<QUuid> m_activeFilterIds;
};

#endif // FILEFILTERWIDGET_H
