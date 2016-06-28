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

private:
   void setCurrentGroupName(const QString &newName);
   void addGroupWithName(const QString &groupName);
   Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
