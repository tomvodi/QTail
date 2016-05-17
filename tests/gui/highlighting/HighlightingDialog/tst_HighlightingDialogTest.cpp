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

QTEST_MAIN(HighlightingDialogTest)

#include "tst_HighlightingDialogTest.moc"
