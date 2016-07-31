/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QList>
#include <QDialog>

namespace Ui {
class FilterDialog;
}
class FilterGroup;
class FilterRule;
class QListWidgetItem;
class QAbstractButton;

/*!
 * \brief The FilterDialog class
 * A dialog to configure all filter groups and their filter rules.
 */
class FilterDialog : public QDialog
{
   Q_OBJECT
   friend class FilterDialogTest;

public:
   explicit FilterDialog(QWidget *parent = 0);
   ~FilterDialog();

   void setFilterGroups(const QList<FilterGroup> &groups);

signals:
   void filterGroupsChanged(const QList<FilterGroup> &filterGrops);

private slots:
   void on_renameGroupButton_clicked();
   void on_addGroupButton_clicked();
   void on_addFilterButton_clicked();
   void on_deleteGroupButton_clicked();
   void on_regexLineEdit_editingFinished();
   void on_caseSensitiveCheckBox_toggled(bool checked);
   void on_filtersListWidget_itemChanged(QListWidgetItem *item);
   void on_filtersListWidget_itemClicked(QListWidgetItem *item);
   void on_filterGroupComboBox_currentIndexChanged(int index);
   void on_deleteFilterButton_clicked();
   void on_buttonBox_clicked(QAbstractButton *button);

private:
   static const int CaseSensitiveDataRole = Qt::UserRole + 1;
   void addDefaultGroup();
   void setCurrentGroupName(const QString &newName);
   void addGroup(const FilterGroup &group);
   void setFilterRules(const QList<FilterRule> &filters);
   void addFilterRuleItem(const FilterRule &filterRule);
   void setCurrentFilterGroupDataFromGui();
   void clearEditWidgetsContent();
   void setEditWidgetsContentForCurrentFilterItem();
   void checkForEnabledDeleteFilterGroupButton();
   QList<FilterGroup> filterGroups() const;
   Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
