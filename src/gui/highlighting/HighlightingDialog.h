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
class QAbstractButton;

class HighlightingDialog : public QDialog
{
   Q_OBJECT
   friend class HighlightingDialogTest;

public:
   explicit HighlightingDialog(QWidget *parent = 0);
   ~HighlightingDialog();

   void setHighlightingRules(const QList<HighlightingRule> &lineRules,
                             const QList<HighlightingRule> &wordRules);

signals:
   void highlightingRulesChanged(const QList<HighlightingRule> &lineRules,
                                 const QList<HighlightingRule> &wordRules);

private slots:
   void on_addRuleButton_clicked();
   void on_deleteRuleButton_clicked();
   void on_buttonBox_clicked(QAbstractButton *button);
   void on_downButton_clicked();
   void on_upButton_clicked();
   void on_bottomButton_clicked();
   void on_topButton_clicked();
   void updateCurrentSelectedRuleValues();

private:
   static int HighlightRuleDataRole;
   Ui::HighlightingDialog *ui;
   HighlightingRule highlightingRuleFromGui() const;
   QList<HighlightingRule> wordHighlightingRules() const;
   QList<HighlightingRule> lineHighlightingRules() const;
   void addNewRuleToListWidget(QListWidget *listWidget, const HighlightingRule &rule);
   void deleteCurrentSelectedRule();
   void setUiForCurrentSelectedItem();
   QListWidgetItem *currentSelectedItem() const;
   void selectListWidgetItem(QListWidgetItem *item);
   void createConnections();
   QList<HighlightingRule> rulesFromListWidget(QListWidget *listWidget) const;
};

#endif // HIGHLIGHTINGDIALOG_H
