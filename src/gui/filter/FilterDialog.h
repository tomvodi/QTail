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
   void on_regexLineEdit_textChanged(const QString &text);
   void on_caseSensitiveCheckBox_toggled(bool checked);
   void on_filtersListWidget_itemChanged(QListWidgetItem *item);

private:
   static const int CaseSensitiveRole = Qt::UserRole + 1;
   void setCurrentGroupName(const QString &newName);
   void addGroupWithName(const QString &groupName);
   Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
