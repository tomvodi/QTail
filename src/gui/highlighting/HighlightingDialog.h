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

#include <include/HighlightingRule.h>

namespace Ui {
class HighlightingDialog;
}
class QListWidget;
class QListWidgetItem;

class HighlightingDialog : public QDialog
{
   Q_OBJECT
   friend class HighlightingDialogTest;

public:
   explicit HighlightingDialog(QWidget *parent = 0);
   ~HighlightingDialog();

   QList<HighlightingRule> wordHighlightingRules() const;
   QList<HighlightingRule> lineHighlightingRules() const;

signals:
   void wordHighlightingRulesChanged(const QList<HighlightingRule> &rules);
   void lineHighlightingRulesChanged(const QList<HighlightingRule> &rules);

private slots:
   void on_addRuleButton_clicked();
   void on_deleteRuleButton_clicked();
   void updateCurrentSelectedRuleValues();

private:
   static int HighlightRuleDataRole;
   Ui::HighlightingDialog *ui;
   HighlightingRule highlightingRuleFromGui() const;
   void addNewRuleToListWidget(QListWidget *listWidget, const HighlightingRule &rule);
   void deleteCurrentSelectedRule();
   void setUiForCurrentSelectedItem();
   QListWidgetItem *currentSelectedItem() const;
};

#endif // HIGHLIGHTINGDIALOG_H
