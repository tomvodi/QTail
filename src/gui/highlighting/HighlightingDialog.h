/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef HIGHLIGHTINGDIALOG_H
#define HIGHLIGHTINGDIALOG_H

#include <QDialog>

namespace Ui {
class HighlightingDialog;
}
class QListWidget;
class QListWidgetItem;

class HighlightingDialog : public QDialog
{
   Q_OBJECT

public:
   explicit HighlightingDialog(QWidget *parent = 0);
   ~HighlightingDialog();

private slots:
   void on_addRuleButton_clicked();
   void on_deleteRuleButton_clicked();

private:
   Ui::HighlightingDialog *ui;
   void addNewRuleToListWidget(QListWidget *listWidget);
   void deleteCurrentSelectedRule();
   QListWidgetItem *currentSelectedItem() const;
};

#endif // HIGHLIGHTINGDIALOG_H
