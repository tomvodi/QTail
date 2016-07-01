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

class FilterDialog : public QDialog
{
   Q_OBJECT
   friend class FilterDialogTest;

public:
   explicit FilterDialog(QWidget *parent = 0);
   ~FilterDialog();

   void setFilterGroups(const QList<FilterGroup> &filterGrops);

private slots:
   void on_renameGroupButton_clicked();
   void on_addGroupButton_clicked();
   void on_addFilterButton_clicked();
   void on_regexLineEdit_editingFinished();
   void on_caseSensitiveCheckBox_toggled(bool checked);
   void on_filtersListWidget_itemChanged(QListWidgetItem *item);
   void on_filterGroupComboBox_currentIndexChanged(int index);

private:
   static const int CaseSensitiveDataRole = Qt::UserRole + 1;
   static const int FilterGroupDataRole   = Qt::UserRole + 2;
   void setCurrentGroupName(const QString &newName);
   void addGroup(const FilterGroup &group);
   void setFilterRules(const QList<FilterRule> &filters);
   void addFilterRule(const FilterRule &filterRule);
   Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
