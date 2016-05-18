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
   void testAddMultipleHighlightingRules();
   void testDeleteHighlighingRule();
   void testDeleteRuleWithMultipleRulesInList();
   void testChangeSelectedRule();
   void testChangingSelectedRule();
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

   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count(), "Added rule wasn't selected");

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

void HighlightingDialogTest::testAddMultipleHighlightingRules()
{
   HighlightingDialog dialog;

   HighlightingRule rule1;
   rule1.setText("Blablalbla");
   HighlightingRule rule2;
   rule2.setText("Rule 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule2);

   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count() == 1, "Adding second rule selected more than one item.");
}

void HighlightingDialogTest::testDeleteHighlighingRule()
{
   HighlightingDialog dialog;

   HighlightingRule rule;
   rule.setText("Blablalbla");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule);
   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   dialog.deleteCurrentSelectedRule();
   QVERIFY2(dialog.ui->wordRulesListWidget->count() == 0, "Selected rule wasn't deleted");
}

void HighlightingDialogTest::testDeleteRuleWithMultipleRulesInList()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule1;
   rule1.setText("Blablalbla");

   HighlightingRule rule2;
   rule2.setText("Test text 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule2);

   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   QListWidgetItem *selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   QVariant selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   HighlightingRule selectedRule = selectedRuleData.value<HighlightingRule>();
   QVERIFY2(selectedRule == rule2, "Wrong selected rule");

   dialog.deleteCurrentSelectedRule();

   QVERIFY2(dialog.ui->wordRulesListWidget->selectedItems().count(), "No selected rule after deleting one rule");
   selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   selectedRule = selectedRuleData.value<HighlightingRule>();
   QVERIFY2(selectedRule == rule1, "Wrong selected rule, probably wrong rule deleted.");
}

/*!
 * \brief HighlightingDialogTest::testChangeSelectedRule
 * Changing the current selected rule should display the rule's setting in ui.
 */
void HighlightingDialogTest::testChangeSelectedRule()
{
   HighlightingDialog dialog;

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule1;
   rule1.setBackgroundColor(Qt::lightGray);
   rule1.setForegroundColor(Qt::yellow);
   rule1.setFont(testFont);
   rule1.setText("Blablalbla");

   HighlightingRule rule2;
   rule2.setBackgroundColor(Qt::black);
   rule2.setForegroundColor(Qt::white);
   rule2.setFont(testFont);
   rule2.setText("Test text 2");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);
   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule2);

   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   QListWidgetItem *selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   QVariant selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   HighlightingRule selectedRule = selectedRuleData.value<HighlightingRule>();
   QVERIFY2(selectedRule == rule2, "Wrong selected rule");

   QVERIFY2(dialog.ui->foregroundColorPicker->currentColor() == rule2.foregroundColor(),
            "Foreground color wasn't set from selected rule");
   QVERIFY2(dialog.ui->backgroundColorPicker->currentColor() == rule2.backgroundColor(),
            "Background color wasn't set from selected rule");
   QVERIFY2(dialog.ui->fontPicker->currentFont() == rule2.font(),
            "Font wasn't set from selected rule");
   QVERIFY2(dialog.ui->regexLineEdit->text() == rule2.text(),
            "Text wasn't set from selected rule");
   QVERIFY2(dialog.ui->caseSensitiveCheckBox->isChecked() == (rule2.caseSensitivity() == Qt::CaseSensitive),
            "Case sensitivity wasn't set from selected rule");
}

/*!
 * \brief HighlightingDialogTest::testChangingSelectedRule
 * Changing the ui, should change the current selected rules values.
 */
void HighlightingDialogTest::testChangingSelectedRule()
{
   HighlightingDialog dialog;
   dialog.show();

   QFont testFont = TestCommon::testFont();
   HighlightingRule rule1;
   rule1.setBackgroundColor(Qt::lightGray);
   rule1.setForegroundColor(Qt::yellow);
   rule1.setFont(testFont);
   rule1.setText("Rule 1 text");

   dialog.addNewRuleToListWidget(dialog.ui->wordRulesListWidget, rule1);

   Q_ASSERT(dialog.ui->wordRulesListWidget->selectedItems().count());

   QColor newForegroundColor(Qt::blue);
   QColor newBackgroundColor(Qt::green);
   testFont.setBold(true);
   testFont.setItalic(true);
   QString testText("New text for rule");
   bool newCaseValue = !dialog.ui->caseSensitiveCheckBox->isChecked();

   dialog.ui->foregroundColorPicker->setCurrentColor(newForegroundColor);
   dialog.ui->backgroundColorPicker->setCurrentColor(newBackgroundColor);
   dialog.ui->fontPicker->setCurrentFont(testFont);
   dialog.ui->regexLineEdit->setText(testText);
   dialog.ui->caseSensitiveCheckBox->setChecked(newCaseValue);

   QListWidgetItem *selectedItem = dialog.ui->wordRulesListWidget->selectedItems().at(0);
   QVariant selectedRuleData = selectedItem->data(HighlightingDialog::HighlightRuleDataRole);
   HighlightingRule selectedRule = selectedRuleData.value<HighlightingRule>();

   QVERIFY2(selectedItem->foreground() == newForegroundColor, "Foreground color wasn't set for list item.");
   QVERIFY2(selectedRule.foregroundColor() == newForegroundColor, "Foreground color wasn't set for selected rule");

   QVERIFY2(selectedItem->backgroundColor() == newBackgroundColor, "Background color wasn't set for list item.");
   QVERIFY2(selectedRule.backgroundColor() == newBackgroundColor, "Background color wasn't set for selected rule");

   QVERIFY2(selectedItem->font() == testFont, "Font wasn't set for list item.");
   QVERIFY2(selectedRule.font() == testFont, "Font wasn't set for selected rule");

   QVERIFY2(selectedItem->text() == testText, "Text wasn't set for list item.");
   QVERIFY2(selectedRule.text() == testText, "Text wasn't set for selected rule");

   QVERIFY2(selectedRule.caseSensitivity() == (newCaseValue ? Qt::CaseSensitive : Qt::CaseInsensitive),
            "Case sensitivity wasn't set for selected rule");
}

QTEST_MAIN(HighlightingDialogTest)

#include "tst_HighlightingDialogTest.moc"
