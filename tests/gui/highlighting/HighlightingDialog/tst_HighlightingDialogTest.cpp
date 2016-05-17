/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <TestCommon.h>
#include <highlighting/HighlightingDialog.h>
#include <ui_HighlightingDialog.h>

class HighlightingDialogTest : public QObject
{
   Q_OBJECT

public:
   HighlightingDialogTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testExclusiveSelection();
   void testAddHighlightingRule();
};

HighlightingDialogTest::HighlightingDialogTest()
{
}

void HighlightingDialogTest::initTestCase()
{
}

void HighlightingDialogTest::cleanupTestCase()
{
}

void HighlightingDialogTest::testExclusiveSelection()
{
   HighlightingDialog dialog;

   dialog.ui->wordRulesListWidget->addItem("Word rule item 1");
   dialog.ui->lineRulesListWidget->addItem("Line rule item 1");

   QAbstractItemModel *wordListModel = dialog.ui->wordRulesListWidget->model();
   QAbstractItemModel *lineListModel = dialog.ui->lineRulesListWidget->model();
   dialog.ui->wordRulesListWidget->selectionModel()->select(wordListModel->index(0, 0), QItemSelectionModel::Select);
   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count(), "No items selected");

   dialog.ui->lineRulesListWidget->selectionModel()->select(lineListModel->index(0, 0), QItemSelectionModel::Select);
   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count() == 0, "Word list item wasn't unselected.");
   QVERIFY2(dialog.ui->lineRulesListWidget->selectedItems().count(), "Line item wasn't selected.");
}

void HighlightingDialogTest::testAddHighlightingRule()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule;
   rule.setBackgroundColor(Qt::lightGray);
   rule.setForegroundColor(Qt::yellow);
   rule.setFont(testFont);
   rule.setText("Blablalbla");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule);

   QListWidgetItem *listItem = dialog.ui->wordRulesListWidget->item(0);

   QVERIFY2(listItem != 0, "No list item was added for new rule");
   QVERIFY2(listItem->background() == rule.backgroundColor(), "Background color wasn't set in list item");
   QVERIFY2(listItem->foreground() == rule.foregroundColor(), "Foreground color wasn't set in list item");
   QVERIFY2(listItem->text() == rule.text(), "Text wasn't set in list item");
   QVERIFY2(listItem->font() == rule.font(), "Font wasn't set in list item");

   QVERIFY2(listItem->data(HighlightingDialog::HighlightRuleDataRole).canConvert<HighlightingRule>(),
            "Highlighting rule data wasn't set in list item");
   HighlightingRule listItemDataRule = listItem->data(HighlightingDialog::HighlightRuleDataRole).value<HighlightingRule>();
   QVERIFY2(listItemDataRule == rule, "Rule in list item isn't the same that was set");
}

QTEST_MAIN(HighlightingDialogTest)

#include "tst_HighlightingDialogTest.moc"
